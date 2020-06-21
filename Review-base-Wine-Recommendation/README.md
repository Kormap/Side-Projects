# Kaggle-Review-base-Wine-Recommendation
Kaggle-Review-base-Wine-Recommendation
  
"Kaggle 리뷰 기반 와인 추천 시스템"   
  
2019년 2학기 데이터마이닝 분석  
  
## Team Member  
* [김수환](https://github.com/sh951011) KWU. elcomm 3rd year    
* [배세영](https://github.com/triplet02) KWU. elcomm 3rd year  
* [박종혁](https://github.com/kaya176) KWU. mathmatic 4rd year  
* 김종휘  KWU. data science 3rd year  
  
## Development Environment  
  
![develenvrm](https://postfiles.pstatic.net/MjAxOTEyMTZfMjUz/MDAxNTc2NDI2NDAxNjUw.is3i2YeTdg18DIbokmU-C2DfRfR2JjzfSlhPdJTbrq0g.P1egeyRXFlZGuyE2FgETGmfEjtPRGv5Bfxrwq0ZSP78g.PNG.sooftware/image.png?type=w773)
  
## Data  
  
캐글에서 제공하는 와인 리뷰 데이터 사용  
![kaggle](https://lh5.googleusercontent.com/cWHG04p70skVyFL14yZ86OFebbM_LjwTBTBedlQ18s2KJw9FFqGRE3y1dZrxYTDg4Pm2MHgKbhY5HJnBwT4zjZycFJ0Vm3eiPQNkOEbXyvMM81lEgI9h8-ygD5v6MU25lYOtqJf3)   
  
### Data Format  
![dataformat](https://lh3.googleusercontent.com/IusnrkZDTCW6yPCIGtxj3z-f6jXv_b0OyNYw8WRh-Ig9UJItb705dmUABHXCxkyuebZshmt90E9iICfu3xE-IyixZvrCeoA8K7d2qFv5nlTKLGfQz1ZZgsPU1Sl7835fkcp1oXqd)  
* 원산지 리뷰 지명 가격 등으로 구성된 약 130,000개 데이터
* 와인 1개당 1개의 리뷰로 일대일 구성
* 2개의 csv file, 1개의 json 파일로 구성   
   
## Program Structure  
  
![programstructure](https://postfiles.pstatic.net/MjAxOTEyMTZfNjUg/MDAxNTc2NDI2NDU5OTk1.YShl25HzFTUQIHPhr10D9Hj2bX5SXt7a-bo1Un0abR4g.1YIU5IyIhcNwZVlIHJJF7QYZZGffDrJMsiyHWX1ogcYg.PNG.sooftware/image.png?type=w773)  
  
## Six Feature  
  
![six_feature](https://lh3.googleusercontent.com/ZgrHreNspd10RRxEXNAuB4ubG8ozGo8X4bO09qEeDr1nY3y745UL-fHdbUxQVbL47GLWclVUszSmOd030-ak0gwL1ywbJaqOZgF6n0DzrM0TejidmhTh0rpacIKGw2ODFqYKXNAB)  
  
Sweetness  Bitterness  Fruity  Acidity  Aging  Softness (단맛 쓴맛 과일향 산도 숙성정도 목넘김)  
점수 배점 : 매우낮음 (1), 낮음 (2), 보통 (3), 높음 (4), 매우높음(5)   
* Sweetness, Bitterness, Acidity   
  + 사용자가 어떤 ‘맛’의 와인을 선호하는지 확인하기 위한 항목   
* Fruity, Aging   
  + 사용자가 어떤 ‘향’의 와인을 선호하는지 확인하기 위한 항목   
* Softness   
  + 사용자가 Soft or Dry 중 어떤 ‘목넘김’을 선호하는지를 확인하기 위한 항목   
  
### User Customizing Question List
  
![user_customizing](https://lh6.googleusercontent.com/EzPZ34Bx24W9-Wm9x4xZZM6noGfCalqH0aQEXAgO_emNXiv8bFExPxp4b1v7QbH67K65KlxJuP4g8K0DaP5kaAZXsLllpyjaV9cjJCGAfEMYvf--v0M0PqpyRS6wgFrxKdLBo4xK)  
  
Q1 - Q6 각각 Sweetness  Bitterness  Fruity  Acidity  Aging  Softness 선호도 측정 질문   
Ex)    
Q1. 좋아하는 커피 or 음료는 무엇인가요? (사용자의 단맛 선호도 조사)  
에스프레소(1점)  아메리카노(2점)  카페라떼(3점)  프라푸치노(4점)  달달한 핫초코 (5점)  
Q2. 좋아하는 초콜렛이 무엇입니까? (사용자의 쓴맛 선호도 조사)  
밀크 초콜렛(1점)  카카오 56%(2점)  카카오 72%(3점)  카카오 82%(4점)  카카오 99.9%(5점)  

## Data Preprocessing  
  
보다 정확한 분석을 위해 리뷰에 의미가 없는 특수문자, 문장부호 ,불용어 (Stop word)를  
제거하고, 대문자를 소문자로 통일하여 문장에서 의미 있는 단어만 추출  
    
### 원 문장 (Raw Sentence)  
아래와 같은 원 문장에 대해 전처리 과정을 가짐  
ex) This spent 20 months in 30% new French oak, an ...  
  
### 특수문자 제거 ('%' ',' '!' ...)  
의미가 없는 특수기호, 문장 부호를 제거  
ex) This spent 20 months in 30 new French oak an ...  
  
### 대소문자 통일  
영문자를 소문자로 통일  
 ex) this spent 20 months in 30 new french oak an ...  
   
### 불용어 (stop word) 제거  
nltk 라이브러리를 이용하여 단어 중 의미가 없는 관사, 전치사 등을 제거  
ex) spent 20 months 30 new french oak …  
  
## Keyword Scoring  
단어 빈도수로 정렬하여 전체 리뷰에서 등장횟수가 1,000회 이상인 키워드 600개의 단어 중  
선정한 평가 항목과 관련된다고 판단한 109개의 키워드를 추출 및 키워드에 점수 부여  
  
![keyword_score](https://lh5.googleusercontent.com/3saCQ7w3dhWRgo_t_pjkAmFxjMQCdvmXKMYV2nOb4zs95McgX_R2m3vPgUJ-wgeMrTOUO-kux_IffC1O8bEUTOWI-2qwPyk-nqMxUxu5uZ62vLxypMGQK-La6BRpue18gzwDmgpR)
   
### 키워드에 각 평가항목별 점수 부여  
  
평가항목에 대해 키워드가 관련이 없다 생각되는 경우 0점 부여  
평가항목에 플러스 요인인 경우 정도에 따라 +2 / +1 점 부여  
평가항목에 마이너스 요인인 경우 정도에 따라 -2 / -1 점 부여  
  
### 앞뒤 수식어에 의해 의미가 반전될 수 있는 경우 - Windowing  
앞뒤로 꾸며주는 단어에 의해서 의미가 크게 변하는 키워드들은 해당 평가항목에 대해  
'x' 표시를 해두고 설정한 window 크기에 따라 앞뒤 단어 중 수식어를 확인하여 점수 부여  
  
미리 찾아놓은 수식어 (매우 긍정, 긍정, 부정, 매우 부정) 리스트에 속한 단어가 있는 경우,  
속한 단어 리스트에 따라 +2, +1, -1, -2 점 부여  
리스트에 속한 단어가 없는 경우는 0점 부여  
  
![window_keyword](https://lh6.googleusercontent.com/Pa9ZdDD7crkckv__dAvEkRrdAMAd_5FqhIQDkTWyhRCmQJlAOPLYk2fjiLelxgOLSrI657ybL3WcMEBwAFCLwynUzL2WrCQWCh8IKfIyzE1cRQaKFM3RTdHJVq6OLESgnnPM_dGU)  
  
ex) … ripe sweet bottling shows plenty **acidity** honeyed orange pineapple flavors …  
전처리를 거친 리뷰 문장이 위와 같은 단어들로 구성되어 있을 때  
![qwe](https://lh3.googleusercontent.com/Jg_wuRPl9QjWJvhmxEIucKAt5JCqdN-03VUMbuE2TFiiVIcnlhA30yXQr_ERx6yc93GaSQRM1_QgjngozdAvoSfIewCXs_F_EEDxoxEJcCnKK7wXVsH1LLfmKRSTabF7a1yhaSUB)  
  
'acidity'라는 단어로 Acidity 평가항목의 점수를 산출할 때,  
'acidity'을 기준으로 설정한 window 크기만큼의 단어 중 수식어 파악  
  
![windowing](https://lh4.googleusercontent.com/S84YVfyaQRNYAZ6tK0HU-53-Y8Yw2iG-qw4t8aMPu14Ny64UydHb90nl-s_9kP3cNTxcho0XOx88H-OpfA1EbNelCUm2fwlEUoxCAn9TaLc1_88tPw7Mr1D2ZPWSmK3LJNKwGIeN)  
  
![mark](https://lh6.googleusercontent.com/Pa9ZdDD7crkckv__dAvEkRrdAMAd_5FqhIQDkTWyhRCmQJlAOPLYk2fjiLelxgOLSrI657ybL3WcMEBwAFCLwynUzL2WrCQWCh8IKfIyzE1cRQaKFM3RTdHJVq6OLESgnnPM_dGU)  
  
설정한 window 내에 plenty 라는 긍정의 수식어가 포함돼있으므로 'acidity'라는 키워드에 대해 +1점을 부여   
  
## Word Embedding - TF-IDF  
자연어를 컴퓨터가 처리 가능하도록 TF-IDF 방식으로 변환  
### TF-IDF  
각각의 문서에서 단어의 갯수를 세는 것뿐만이 아니라 전체 말뭉치 (Corpus) 에서 단어의  
개수도 함께 세는 방법. 특정 단어가 문서 내에 얼마나 자주 등장하는지를 TF (단어 빈도) 와  
어떤 단어가 문서 전체 집합에서 얼마나 많이 나오는지를 나타내는 IDF (역문서 빈도) 로 이 둘의 곱으로 값을 구하는 방법   
  
* TF = 특정 문서에서 단어가 나타난 수 / 특정 문서에 있는 전체 단어의 개수  
* IDF = log(말뭉치에서의 전체 문서의 수 / 말뭉치에서 해당 단어가 나타난 문서의 수)  
  
word2vec은 앞 뒤와 같이 순서가 중요한 경우에 쓰이는 방법이고, BOW처럼 단순히 단어를 세는 방식이 아닌  
전체 말뭉치에서의 단어의 개수도 고려해주는 TF-IDF 방법 사용  
  
## Classifier - Naive Bayes  
각 평가항목에 대한 점수를 분류하는 분류기로 Naive Bayes 사용  
  
### Multinomial Naive Bayes Classifier  
텍스트 분류에 있어서 어느 정도 좋은 성능을 낸다고 평가받는 모델이며,  
나이브 베이즈는 각 단어가 독립일 때 사용되므로 앞뒤 문맥 파악이 아닌 키워드 추출로   
와인 특성을 파악하는 시도이므로 적절한 분류기라고 판단  
  
### Using Classifier on each Feature  
6개의 평가항목에 대하여 1점 - 5점까지의 5개의 점수에 대해 한 번에 분류하게 되면  
5^6이라는 경우의 수가 나오기 때문에 이를 보완하기 위하여 각 속성별로 Classifier를 적용하여  
1개의 Classifier 당 5개의 경우의 수만 분류 하도록 적용  
  
![each_classifier](https://lh5.googleusercontent.com/n_9PWbvJCn6nB0F7SfTBPJ_LTADNo-6oEPattudcN1FBpf-oK5t5jwMLnuOZU77xqqTCvqvx8s81vRTkDcyS1Z3GEfmjo3F2f-Xaer1UbZG19G5jKbfaV8seQBlMrCYfbrroIrop)  
  
## Graphic User Interface & Visualization  
tkinter, matplotlib 활용 사용자 인터페이스 및 와인 평가항목별 점수 시각화  
  
![gui](https://lh6.googleusercontent.com/u3tKrqn6mm5aRKYVLxSxNCZ3zRCB-8AvqFa0sYaZ5q4YVypxvPPGvkxfDNJcomJNQh1AGpneYvfz0ke1aJOC4MEbHkXT9pPgpVf_gAlRMfuSbmYjrY4EluQnf90wiLPTc4POKCup)  
  
![radar_chart](https://lh6.googleusercontent.com/71rFpsU_kd6DFrVN8pCp7pDryGqYnFk15nLwhK1X_5GFi12EiwFGuurGLSv0_gwd1nekVBXLFE2AdygwddTGCeQ90eTYU79oZ2W9OUOZGDiAtbdHejRuwtDF4IMTyoSPzXBony8i)  
  

## Reference  
* Kaggle Wine-Review : https://www.kaggle.com/zynicide/wine-reviews
