'''
  -*- coding: utf-8 -*-

  2019 - 2학기 - 정보융합학부 데이터사이언스
  데이터마이닝 분석 프로젝트

  주제 : " 리뷰 기반 와인 추천 시스템 "

  data source : https://www.kaggle.com/zynicide/wine-reviews

    전자통신공학과   2014707073 김수환
    정보융합학부     2017204009 김종휘
    수학과          2014603023 박종혁
    전자통신공학과   2014707010 배세영
'''

import numpy as np
import pandas as pd
from sklearn.metrics import accuracy_score
from sklearn.utils import shuffle
from base_func import get_attribute_label, split_sentence, auto_score_to_csv, predict_score_to_csv
from wine import Wine
from keyword_class import Keyword
from definition import LABEL_PATH, DATA_PATH,COMP_PATH, TRAIN_SIZE, TEST_SIZE, ATTRIBUTE_NUM, WINE_SCORE_PATH, PREDICT_SCORE_PATH, HAND_LABEL_PATH
from word_embed import transform_tfidf
from sklearn.model_selection import cross_val_score, StratifiedKFold
from sklearn.naive_bayes import MultinomialNB

# 레이블 파일에서 키워드 데이터 로드
def keyword_loader():
    label = pd.read_csv(LABEL_PATH)
    keywords = label['keyword']
    keyword_list = list()
    for idx, keyword in enumerate(keywords):
        keyword_list.append(Keyword(keyword=keyword, sweet = label['sweet'][idx],
                                    bitter=label['bitter'][idx], fruity=label['fruity'][idx],
                                    acidity=label['acidity'][idx], aging=label['aging'][idx],
                                    soft=label['soft'][idx]))
    return keyword_list

# 데이터 파일에서 와인 데이터 로드
def wine_loader():
    data = pd.read_csv(COMP_PATH)
    data = shuffle(data) # data shuffle
    wine_list = list()

    for idx, review_price in enumerate(zip(data['description'], data['price'], data['title'])):
        review, price, comp = review_price
        if idx == TRAIN_SIZE + TEST_SIZE: break
        wine_list.append(Wine(review=review,price=price,name=comp))
    return wine_list[:TRAIN_SIZE], wine_list[TRAIN_SIZE:TRAIN_SIZE+TEST_SIZE]

# Hand Label Test
def hand_label_loader():
    data = pd.read_csv(HAND_LABEL_PATH)
    data = shuffle(data)
    test_list = list()
    for idx, column in enumerate(zip(data['sweet'],data['bitter'],data['fruity'],data['acidity'],data['aging'],data['soft'], data['review'])):
        sweet, bitter, fruity, acidity, agint, soft, review = column
        wine = Wine(review=review,price='',name='')
        wine.auto_score = np.array([sweet, bitter, fruity, acidity, agint, soft])
        wine.attr_label_list = get_attribute_label()
        wine._extract_keyword()
        wine._get_score(update=False)
        test_list.append(wine)
    return test_list

if __name__ == '__main__':
    attrs = ['sweet', 'bitter', 'fruity', 'acidity', 'aging', 'soft']
    keyword_list = keyword_loader()  # get keyword list
    train_list, _ = wine_loader()  # get wine list
    wine_list = train_list #+ test_list # total wine list
    test_list = hand_label_loader()
    # 와인 자동 스코어링
    for wine in wine_list:
        wine.auto_scoring()

    auto_score_to_csv(train_list=train_list)

    # Predict ===
    clf_list = [MultinomialNB() for _ in range(ATTRIBUTE_NUM)]

    for idx, attr in enumerate(attrs):
        train_tfidf, y_hyp = transform_tfidf(data_list=train_list, attr=attr)
        clf_list[idx].fit(X=train_tfidf, y=y_hyp)

    predict_scores = [[] for _ in range(ATTRIBUTE_NUM)]
    for idx, attr in enumerate(attrs):
        test_tfidf, y_hyp = transform_tfidf(data_list=test_list, attr=attr)
        predict_soft = clf_list[idx].predict(test_tfidf)
        predict_scores[idx] = predict_soft
        print("Naive Bayes ", attr, " Accuracy Score -> ", accuracy_score(predict_soft, y_hyp)*100)

    predict_scores = np.array(predict_scores).transpose()
    for wine, predict_score in zip(wine_list, predict_scores):
        wine.predict_score += np.array(predict_score)

    predict_score_to_csv(wine_list=wine_list)
    # =============================================================

"""
    # K-Fold Cross Validation ===
    skf = StratifiedKFold(n_splits=10, shuffle=True, random_state=1)
    clf = MultinomialNB()
    for idx, attr in enumerate(attrs):
        print("attribute : ", attr, " Start...")
        tfidf, y_hyp = transform_tfidf(data_list=wine_list, attr=attr)
        y_hyp = [int(round(item, 0)) for item in y_hyp]
        score = np.mean(cross_val_score(clf, tfidf, y_hyp, cv=skf, n_jobs=-1))
        print(attr, "attr score : ", round(score,2))
        print("attribute : ", attr, " End")
    # ==============================================================
"""