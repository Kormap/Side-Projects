from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.feature_extraction.text import CountVectorizer
from nltk.corpus import words
import nltk
nltk.download('words')

# 알파벳, 숫자, 공백 제외한 문자 필터링
def str_filtering(sentence):
    new_sentence = str()
    for ch in sentence:
        if ch.isalpha() or ch.isdigit() or ch == ' ':
            new_sentence += ch.lower()
    return new_sentence

# Get TF-IDF Vector
def transform_tfidf(data_list, attr):
    # 문자열이 담긴 리스트를 공백으로 분리한
    # 문자열로 만드는 함수
    def list_to_string(list_):
        result = str()
        for idx, str_ in enumerate(list_):
            if idx == 0: result += str_
            result += (' ' + str_)
        return result

    samples = list()    # attr 관련 키워드 저장 리스트
    labels = list()  # 레이블링 된 점수

    for idx, df in enumerate(data_list):
        data_list[idx].review = str_filtering(df.review)  # 문자열 필터링
        samples.append(list_to_string(data_list[idx].get_keywords(attr)))  # 해당 attr 관련 키워드만 받아와서 docs에 추가
        labels.append(float(data_list[idx].get_score(attr)))

    # instantiate CountVectorizer()
    count_vectorizer = CountVectorizer(analyzer = 'word',
                                       lowercase = True,
                                       tokenizer = None,
                                       preprocessor = None,
                                       stop_words = 'english',
                                       min_df = 2,
                                       vocabulary = set(words.words()))
    # this steps generates word counts for the words in your docs
    word_count_vector = count_vectorizer.fit_transform(samples)

    tfidf_transformer = TfidfTransformer()
    tfidf = tfidf_transformer.fit_transform(word_count_vector)
    return tfidf, [int(round(item, 0)) for item in labels]