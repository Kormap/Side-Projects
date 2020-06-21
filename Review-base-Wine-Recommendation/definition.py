# define Constants
LABEL_PATH = './data/winelabeling.csv'
DATA_PATH = './data/wine_detail.csv'
COMP_PATH = './data/wine_comp.csv'
HAND_LABEL_PATH = './data/wine_labeled.csv'
WINE_SCORE_PATH = './data/wine_score.csv'
PREDICT_SCORE_PATH = './data/predict_score.csv'
STR_POSTV = ['highest', 'extremely', 'powerfully']
POSTV = ['high', 'more', 'full', 'plenty', 'thoroughly', 'entirely', 'enough', 'powerful',
         'strong', 'lots', 'especially', 'intensely', 'mildly', 'overly', 'surprisingly',
         'wonderfully', 'deeply', 'additional', 'obvious', 'higher', 'evident', 'enormously',
         'enhanced', 'greater', 'completely', 'impressively', 'heavily', 'highly', 'velvety',
         'extreme', 'dramatic', 'absolutely', 'intensity', 'impressive', 'vibrant']
NEGTV = ['low', 'light', 'less', 'lacks', 'lighter', 'lacking']
STR_NEGTV = ['dont', 'doesnt', 'not',  'never']
TRAIN_SIZE = 50000
TEST_SIZE = 30
ATTRIBUTE_NUM = 6
BASE_SCORE = 3