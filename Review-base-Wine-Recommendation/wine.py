import numpy as np
import pandas as pd
import csv
import re
from base_func import split_sentence, windowing, get_attribute_label
from definition import LABEL_PATH, ATTRIBUTE_NUM, BASE_SCORE

# Wine Class
class Wine:
    # 각 와인에 대한 데이터 저장
    def __init__(self, review, price, name):
        self.name = name
        self.review = review
        self.price = price
        self.auto_score = np.array([BASE_SCORE] * ATTRIBUTE_NUM).astype('float64')
        self.predict_score = np.array([0] * ATTRIBUTE_NUM).astype('float64')
        self.targets = None  # 키워드
        self.score_table = None  # 스코어
        self.attr_label_list = get_attribute_label()  # 속성별 label 2차원 리스트
        self.attr_kwd_list = [[] for _ in range(6)]   # 리뷰에서 뽑은 label에 해당하는 키워드 2차원 리스트

    # review에서 키워드 추출 및 스코어테이블 생성
    def _extract_keyword(self):
        def get_score_list(target):
            f = open(LABEL_PATH, 'r', encoding='utf-8')
            data = csv.reader(f, delimiter=',')
            next(data)

            for row in data:
                if row[1] == target:
                    tmp = [row[idx] for idx in range(2,2 + ATTRIBUTE_NUM)]
                    tmp = [int(item) if item.isdecimal() else item for item in tmp]
                    return tmp

        data = pd.read_csv(LABEL_PATH)
        splited = re.split('[.?!, ]', self.review)  # . ? ! 기준으로 분리
        splited = [item for item in splited if item != '']  # split한 리스트에서 '' 제거
        keywords = np.array(data['keyword'])
        target_list = list()

        for word in splited:
            if word in keywords:
                target_list.append(word)

        score_table = dict()
        for target in target_list:
            score_table[target] = get_score_list(target)

        self.score_table = score_table

    # 스코어 테이블 기반으로 속성별 스코어 산출
    def _get_score(self, update = True):
        score = np.array([0] * ATTRIBUTE_NUM).astype('float64')
        zero_count = [0] * ATTRIBUTE_NUM
        table_len = len(self.score_table)
        for key_value in zip(self.score_table.keys(), self.score_table.values()):
            key, value = key_value  # key == 현재 키워드
            # Windowing
            windowed = None
            if 'x' in value:
                while 'x' in value:
                    sentence_list = split_sentence(self.review)
                    for sentence in sentence_list:
                        if key in sentence:
                            window_score, windowed = windowing(sentence=sentence, base_word=key, window_size=3)
                            for idx, attr_label in enumerate(self.attr_label_list):
                                if key in attr_label:
                                    self.attr_kwd_list[idx].extend(windowed)
                            if 'x' not in value: break
                            value[value.index('x')] = BASE_SCORE + window_score
                            break
            # Not Windowing
            else:
                for idx, attr_label in enumerate(self.attr_label_list):
                    if key in attr_label:
                        self.attr_kwd_list[idx].append(key)

            for idx, attr_kwd in enumerate(self.attr_kwd_list):
                if len(attr_kwd) == 0: self.attr_kwd_list[idx].append('wine')

            for idx, item in enumerate(value):
                if item == 0: zero_count[idx] += 1
            score += np.array(value).astype('float64')

        for idx in range(ATTRIBUTE_NUM):
            if table_len - zero_count[idx] != 0:
                score[idx] = score[idx] / (table_len - zero_count[idx])

        for idx, item in enumerate(score):
            if item > 2:
                score[idx] = 2
            elif item < -2:
                score[idx] = -2
        score = np.array([round(item,0) for item in score]).astype('float64')
        if update: self.auto_score += score

    # 위에 정의한 함수들 이용하여 자동 스코어링
    def auto_scoring(self):
        self._extract_keyword()
        self._get_score()

    def get_keywords(self, attr):
        idx = {attr == 'sweet': 0, attr == 'bitter': 1, attr == 'fruity': 2,
               attr == 'acidity': 3, attr == 'aging': 4, attr == 'soft': 5}.get(True, None)

        if idx == None:
            print("Class Wine : get_keywords() - Invalid attr")

        return self.attr_kwd_list[idx]

    def get_score(self, attr):
        idx = {attr == 'sweet': 0, attr == 'bitter': 1, attr == 'fruity': 2,
               attr == 'acidity': 3, attr == 'aging': 4, attr == 'soft': 5}.get(True, None)

        if idx == None:
            print("Class Wine : get_score() - Invalid attr")

        return self.auto_score[idx]