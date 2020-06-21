import re
import pandas as pd
from definition import LABEL_PATH, STR_POSTV, POSTV, STR_NEGTV, NEGTV, ATTRIBUTE_NUM, PREDICT_SCORE_PATH, WINE_SCORE_PATH
from nltk.corpus import stopwords
from word_embed import str_filtering

# review를 문장 단위로 분해
def split_sentence(paragraph):
    splited = re.split("[.?!]",paragraph)
    splited = [item for item in splited if item != '']
    return splited

# 레이블 파일에서 각 속성별 키워드를 분류
def get_attribute_label():
    data = pd.read_csv(LABEL_PATH)
    attr_names = ['sweet', 'bitter', 'fruity', 'acidity', 'aging', 'soft']
    attr_list = list()
    for attr_name in attr_names:
        attr = list()
        for i in range(len(data)):
            if data[attr_name][i] != '0':
                attr.append(data['keyword'][i])
        attr_list.append(attr)
    return attr_list

# 특정 키워드에 대한 문맥상의 정도 표현 고려
# Ex) the acid is 'low'  && the acid is 'high' 와 같은 문장 고려
def windowing(sentence, base_word, window_size=3):
    def remove_stopword(window_list):
        stop_words = stopwords.words('english')  # 리스트 형태의 stopwords
        filter_words = list()
        for word in window_list:
            if word not in stop_words:
                filter_words.append(word)
        return filter_words
    sentence = str_filtering(sentence)
    splited = re.split('[, ]', sentence)
    splited = [word for word in splited if word != '']

    if base_word not in sentence:
        return 0

    for word in splited:
        if base_word in word: base_word = word

    base_index = splited.index(base_word)
    tmp_index_low = base_index - window_size
    tmp_index_high = base_index + window_size

    if tmp_index_low < 0: tmp_index_low = 0
    if tmp_index_high >= len(splited): tmp_index_high = len(splited)

    windowed = splited[tmp_index_low:tmp_index_high]

    score = 0
    for item in windowed:
        score = {item in POSTV: 1, item in NEGTV: -1, item in STR_POSTV: 2, item in STR_NEGTV: -2}.get(True, 0)

    windowed = remove_stopword(windowed)
    return score, windowed

def auto_score_to_csv(train_list):
    seed = {'name':[], 'price':[] , 'sweet':[], 'bitter':[], 'fruity':[], 'acidity':[], 'aging':[], 'soft':[]}
    for wine in train_list:
        seed['name'].append(wine.name)
        seed['price'].append(wine.price)
        seed['sweet'].append(wine.auto_score[0])
        seed['bitter'].append(wine.auto_score[1])
        seed['fruity'].append(wine.auto_score[2])
        seed['acidity'].append(wine.auto_score[3])
        seed['aging'].append(wine.auto_score[4])
        seed['soft'].append(wine.auto_score[5])
    wine_score = pd.DataFrame(seed)
    wine_score.to_csv(WINE_SCORE_PATH, encoding='utf-8', index=False)


def predict_score_to_csv(wine_list):
    seed = {'name': [], 'price': [], 'sweet': [], 'bitter': [], 'fruity': [], 'acidity': [], 'aging': [],
            'soft': []}
    for wine in wine_list:
        seed['name'].append(wine.name)
        seed['price'].append(wine.price)
        seed['sweet'].append(wine.predict_score[0])
        seed['bitter'].append(wine.predict_score[1])
        seed['fruity'].append(wine.predict_score[2])
        seed['acidity'].append(wine.predict_score[3])
        seed['aging'].append(wine.predict_score[4])
        seed['soft'].append(wine.predict_score[5])
    predict_score = pd.DataFrame(seed)
    predict_score.to_csv(PREDICT_SCORE_PATH, encoding='utf-8', index=False)


def get_distance(user, data):
    dist = 0
    for idx in range(ATTRIBUTE_NUM):
        dist += (user[idx]-data[idx])**2
    dist = dist**0.5

    return dist

def recommend(user, wine_list, num):
    tmp = list()
    distance = list()
    final_recommend = list()
    for wine in wine_list:
        distance.append(get_distance(user, wine.predict_score))
        tmp.append((wine.name, wine.price, wine.predict_score))
    distance, tmp = zip(*sorted(zip(distance, tmp)))
    for idx in range(num):
        final_recommend.append(tmp[idx])

    return final_recommend