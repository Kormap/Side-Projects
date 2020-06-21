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

import tkinter as tk
import numpy as np
import matplotlib.pyplot as plt
import os
import pandas as pd

WINE_SCORE_PATH = './data/predict_score.csv'
labels = ['SWEETNESS', 'BITTERNESS', 'FRUTIY', 'ACIDITY', 'AGING', 'SOFTNESS']
markers = [0, 1, 2, 3, 4, 5]
str_markers = ["0", "1", "2", "3", "4", "5"]

# sub_button_action
def remove_all_files():
    PATH = "./image"
    files = os.listdir(PATH)
    if len(files) == 0:
        return 0
    for i in files:
        os.remove(PATH + "/" + i)
    return 1

# button_action
def make_radar_chart(name, stats, attribute_labels=labels, plot_markers=markers, plot_str_markers=str_markers,
                     user=False):
    labels = np.array(attribute_labels)

    angles = np.linspace(0, 2 * np.pi, len(labels), endpoint=False)
    stats = np.concatenate((stats, [stats[0]]))
    angles = np.concatenate((angles, [angles[0]]))

    fig = plt.figure()
    ax = fig.add_subplot(111, polar=True)
    if user == False:
        ax.plot(angles, stats, 'o-', linewidth=2, color='blue')
    else:
        ax.plot(angles, stats, 'o-', linewidth=2, color='red')
    ax.fill(angles, stats, alpha=0.25)
    ax.set_thetagrids(angles * 180 / np.pi, labels)
    plt.yticks(markers)
    ax.set_title(name)
    ax.grid(True)
    fig.savefig("./image/%s.png" % name)
    return plt.show()


# recommend function
def recommend(user, num):
    def predict_score_loader():
        tmp_data = list()
        predict_data = list()
        prediction = pd.read_csv('./data/predict_score.csv')
        for column in prediction.keys()[2:]:
            tmp_data.append(prediction[column])
        tmp_data = np.array(tmp_data).astype('int32').transpose().tolist()

        for column in prediction.keys()[:2]:
            predict_data.append(prediction[column])
        predict_data = np.array(predict_data).transpose().tolist()

        for idx in range(len(prediction)):
            predict_data[idx].append(tmp_data[idx])
        return predict_data

    def get_distance(user, data):
        dist = 0
        for idx in range(6):
            dist += (user[idx] - data[idx]) ** 2
        dist = dist ** 0.5

        return dist

    predict_data = predict_score_loader()

    tmp = list()
    distance = list()
    final_recommend = list()
    for wine in predict_data:
        distance.append(get_distance(user, wine[2]))
        tmp.append((wine[0], wine[1], wine[2]))
    distance, tmp = zip(*sorted(zip(distance, tmp)))
    for idx in range(num):
        final_recommend.append(tmp[idx])

    return final_recommend


# draw_graph
def get_user_score():
    remove_all_files()
    Q1 = RadioVariety_1.get()
    Q2 = RadioVariety_2.get()
    Q3 = RadioVariety_3.get()
    Q4 = RadioVariety_4.get()
    Q5 = RadioVariety_5.get()
    Q6 = RadioVariety_6.get()
    score = [Q1, Q2, Q3, Q4, Q5, Q6]

    final = recommend(score, num=3)  # 추천 결과를 받음
    print(final[0][0])
    # final_func return [[wine_name , wine_price  , score],[...],[...]]

    wine_name = [final[0][0], final[1][0], final[2][0]]
    wine_price = [final[0][1], final[1][1], final[2][1]]
    wine_score = [final[0][2], final[1][2], final[2][2]]

    # real
    for idx in range(3):
        make_radar_chart(str(wine_name[idx]) + "(" + str(wine_price[idx]) + "$)", wine_score[idx])
    make_radar_chart("User", score, user=True)

    show_image()
    return wine_name


def show_image():
    image_list = os.listdir("./image")
    top = tk.Toplevel(window)
    top.title("Graph")
    # print(image_list)
    # 이미지 불러오기
    PATH = "./image/"
    image1 = tk.PhotoImage(file=PATH + image_list[0])
    image2 = tk.PhotoImage(file=PATH + image_list[1])
    image3 = tk.PhotoImage(file=PATH + image_list[2])
    image4 = tk.PhotoImage(file=PATH + image_list[3])

    label1 = tk.Label(top, image=image1)
    label2 = tk.Label(top, image=image2)
    label3 = tk.Label(top, image=image3)
    label4 = tk.Label(top, image=image4)

    label1.grid(row=0, column=0)
    label2.grid(row=0, column=1)
    label3.grid(row=1, column=0)
    label4.grid(row=1, column=1)

    top.mainloop()

if __name__ == '__main__':
    # 기본적인 창
    window = tk.Tk()
    window.title("와인추천")
    # window.geometry("500x600")
    window.configure(background='white')

    # 구성 - Question
    Q1 = tk.Label(window, text="Q1. 좋아하는 커피 or 음료는 무엇인가요?", font=("나눔스퀘어", 12), bg='skyblue')
    Q1.grid(row=0, column=0, columnspan=5, padx=10, pady=10, stick='WE')

    Q2 = tk.Label(window, text='Q2. 좋아하는 초콜렛은 어느것입니까?', font=("나눔스퀘어", 12), bg='skyblue')
    Q2.grid(row=2, column=0, columnspan=5, padx=10, pady=10, stick='WE')

    Q3 = tk.Label(window, text='Q3. 과일(특히 베리종류) 맛, 향을 좋아하십니까?', font=("나눔스퀘어", 12), bg='skyblue')
    Q3.grid(row=4, column=0, columnspan=5, padx=10, pady=10, stick='WE')

    Q4 = tk.Label(window, text='Q4. 신맛을 즐겨하는 편이십니까?', font=("나눔스퀘어", 12), bg='skyblue')
    Q4.grid(row=6, column=0, columnspan=5, padx=10, pady=10, stick='WE')

    Q5 = tk.Label(window, text='Q5. 좋아하는 향이 무엇입니까?', font=("나눔스퀘어", 12), bg='skyblue')
    Q5.grid(row=8, column=0, columnspan=5, padx=10, pady=10, stick='WE')

    Q5 = tk.Label(window, text='Q6. 어떤 목넘김을 선호하나요?', font=("나눔스퀘어", 12), bg='skyblue')
    Q5.grid(row=10, column=0, columnspan=5, padx=10, pady=10, stick='WE')

    # 구성 - Button
    RadioVariety_1 = tk.IntVar()
    RadioVariety_2 = tk.IntVar()
    RadioVariety_3 = tk.IntVar()
    RadioVariety_4 = tk.IntVar()
    RadioVariety_5 = tk.IntVar()
    RadioVariety_6 = tk.IntVar()
    # Q1
    R11 = tk.Radiobutton(window, text="에스프레소", bg='white', value=1, variable=RadioVariety_1)
    R11.grid(row=1, column=0)

    R12 = tk.Radiobutton(window, text="아메리카노", bg='white', value=2, variable=RadioVariety_1)
    R12.grid(row=1, column=1)

    R13 = tk.Radiobutton(window, text="카페라떼", bg='white', value=3, variable=RadioVariety_1)
    R13.grid(row=1, column=2)

    R14 = tk.Radiobutton(window, text="프라푸치노", bg='white', value=4, variable=RadioVariety_1)
    R14.grid(row=1, column=3)

    R15 = tk.Radiobutton(window, text="달달한 핫초코", bg='white', value=5, variable=RadioVariety_1)
    R15.grid(row=1, column=4)
    # Q2
    R21 = tk.Radiobutton(window, text="밀크 초콜렛", bg='white', value=1, variable=RadioVariety_2)
    R21.grid(row=3, column=0)

    R22 = tk.Radiobutton(window, text="카카오 56%", bg='white', value=2, variable=RadioVariety_2)
    R22.grid(row=3, column=1)

    R23 = tk.Radiobutton(window, text="카카오 72%", bg='white', value=3, variable=RadioVariety_2)
    R23.grid(row=3, column=2)

    R24 = tk.Radiobutton(window, text="카카오 82%", bg='white', value=4, variable=RadioVariety_2)
    R24.grid(row=3, column=3)

    R25 = tk.Radiobutton(window, text="카카오 99.9%", bg='white', value=5, variable=RadioVariety_2)
    R25.grid(row=3, column=4)
    # Q3
    R31 = tk.Radiobutton(window, text="매우 싫어함", bg='white', value=1, variable=RadioVariety_3)
    R31.grid(row=5, column=0)

    R32 = tk.Radiobutton(window, text="싫어하는 편", bg='white', value=2, variable=RadioVariety_3)
    R32.grid(row=5, column=1)

    R33 = tk.Radiobutton(window, text="보통", bg='white', value=3, variable=RadioVariety_3)
    R33.grid(row=5, column=2)

    R34 = tk.Radiobutton(window, text="좋아하는 편", bg='white', value=4, variable=RadioVariety_3)
    R34.grid(row=5, column=3)

    R35 = tk.Radiobutton(window, text="매우 좋아함", bg='white', value=5, variable=RadioVariety_3)
    R35.grid(row=5, column=4)
    # Q4
    R41 = tk.Radiobutton(window, text="매우 싫어함", bg='white', value=1, variable=RadioVariety_4)
    R41.grid(row=7, column=0)

    R42 = tk.Radiobutton(window, text="싫어함", bg='white', value=2, variable=RadioVariety_4)
    R42.grid(row=7, column=1)

    R43 = tk.Radiobutton(window, text="보통", bg='white', value=3, variable=RadioVariety_4)
    R43.grid(row=7, column=2)

    R44 = tk.Radiobutton(window, text="좋아함", bg='white', value=4, variable=RadioVariety_4)
    R44.grid(row=7, column=3)

    R45 = tk.Radiobutton(window, text="매우 좋아함", bg='white', value=5, variable=RadioVariety_4)
    R45.grid(row=7, column=4)
    # Q5
    R51 = tk.Radiobutton(window, text="상쾌한 꽃향", bg='white', value=1, variable=RadioVariety_5)
    R51.grid(row=9, column=0)

    R52 = tk.Radiobutton(window, text="은은한 꽃향", bg='white', value=2, variable=RadioVariety_5)
    R52.grid(row=9, column=1)

    R53 = tk.Radiobutton(window, text="보통", bg='white', value=3, variable=RadioVariety_5)
    R53.grid(row=9, column=2)

    R54 = tk.Radiobutton(window, text="버섯 및 흙향", bg='white', value=4, variable=RadioVariety_5)
    R54.grid(row=9, column=3)

    R55 = tk.Radiobutton(window, text="오래된 흙향", bg='white', value=5, variable=RadioVariety_5)
    R55.grid(row=9, column=4)
    # Q6
    R61 = tk.Radiobutton(window, text="Dry", bg='white', value=1, variable=RadioVariety_6)
    R61.grid(row=11, column=0)

    R62 = tk.Radiobutton(window, text="off-Dry", bg='white', value=2, variable=RadioVariety_6)
    R62.grid(row=11, column=1)

    R63 = tk.Radiobutton(window, text="medium", bg='white', value=3, variable=RadioVariety_6)
    R63.grid(row=11, column=2)

    R64 = tk.Radiobutton(window, text="Soft", bg='white', value=4, variable=RadioVariety_6)
    R64.grid(row=11, column=3)

    R65 = tk.Radiobutton(window, text="Very Soft", bg='white', value=5, variable=RadioVariety_6)
    R65.grid(row=11, column=4)

    ResultButton = tk.Button(window, text='결과보기!', command=get_user_score)
    ResultButton.grid(row=14, column=0, columnspan=5)

    window.mainloop()