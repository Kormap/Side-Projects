'''
  -*- coding: utf-8 -*-

  키워드 버튼 클릭 시 해당 키워드의 순위 변동을
  시각적으로 보여주는 기능 구현

  Blog : https://blog.naver.com/sooftware
  GitHub : https://github.com/sh951011

'''
import pandas as pd
from PyQt5 import QtCore, QtGui, QtWidgets, Qt
from PyQt5 import QtCore
import matplotlib.pyplot as plt

NEW_WINDOW_WIDTH = 1000
NEW_WINDOW_HEIGHT = 500

class KeywordTrendWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None, keyword = None):
        super(KeywordTrendWindow, self).__init__(parent)
        self.resize(NEW_WINDOW_WIDTH, NEW_WINDOW_HEIGHT)
        self.setMinimumSize(QtCore.QSize(NEW_WINDOW_WIDTH, NEW_WINDOW_HEIGHT))
        self.centralwidget = QtWidgets.QWidget(self)
        self.setWindowTitle("키워드 순위 변동")
        self.keyword = keyword
        self.draw_keyword_trend()

    # 마우스로 클릭한 버튼에 세팅된 키워드를
    # 넘겨받아 해당 키워드의 순위 변동을 리스트로 저장
    def get_ranks_times(self, keyword):
        def get_rank(series, keyword):
            if len(series[series == keyword]) != 0:
                index = int(series[series == keyword].index[0].replace('Rank', ''))
                return index
            else:
                return None
        read = pd.read_csv("./data/data.csv", encoding="utf-8")
        ENGINE_NUM = 3        # ENGINE_NUM은 for loop 한 번에 -3씩 진행되어야 하므로 상수로 3을 이용한다
        PERIOD_MINUTE = 1     # 데이터를 가져올 주기 (minute)를 정하는 변수.
                              # 1분마다 크롤링을 해서 데이터를 저장하는 프로그램이라 생각하고 기준을 minute으로 잡음
        n_ranks = list()   # 실시간 네이버 검색어 Top 10
        d_ranks = list()   # 실시간 다음 검색어 Top 10
        g_ranks = list()   # 실시간 구글 검색어 Top 10
        for i in range(7):
            # Fix index out of range
            if len(read) >= 1 + i * ENGINE_NUM * PERIOD_MINUTE:
                d_series = read.iloc[-1 - i * ENGINE_NUM * PERIOD_MINUTE]
                # get_rank()의 결과가 None일 경우 Skip
                if get_rank(d_series, keyword) != None:
                    d_ranks.append([11 - get_rank(d_series, keyword), d_series.values[0]])
                else:
                    d_ranks.append([0, d_series.values[0]])
            # Fix index out of range
            if len(read) >= 2 + i * ENGINE_NUM * PERIOD_MINUTE:
                n_series = read.iloc[-2 - i * ENGINE_NUM * PERIOD_MINUTE]
                # get_rank()의 결과가 None일 경우 Skip
                if get_rank(n_series, keyword) != None:
                    n_ranks.append([11 - get_rank(n_series, keyword), n_series.values[0]])
                else:
                    n_ranks.append([0, n_series.values[0]])
            # Fix index out of range
            if len(read) >= 3 + i * ENGINE_NUM * PERIOD_MINUTE\
                    :
                g_series = read.iloc[-3 - i * ENGINE_NUM * PERIOD_MINUTE]
                # get_rank()의 결과가 None일 경우 Skip
                if get_rank(g_series, keyword) != None:
                    g_ranks.append([11 - get_rank(g_series, keyword), g_series.values[0]])
                else:
                    g_ranks.append([0, g_series.values[0]])

            # 최근 데이터로부터 7개의 데이터를 가져온다 넘겨받은 키워드의 Rank와 Time 정보를 가져온다
            # 데이터 저장이 아래에서부터 다음 -> 네이버 -> 구글 순으로 되어 있으므로, 순서대로 가져온다
            # 데이터 저장은 [(Rank, Time), ..., (Rank, Time)] 형식으로 저장한다

        # 최근 데이터부터 가져오므로 뒤의 작업에서
        # 과거 -> 최근 형태로 그래프를 그리기 위해
        # reverse()를 이용해서 뒤집어준다
        n_ranks.reverse()
        d_ranks.reverse()
        g_ranks.reverse()
        return n_ranks, d_ranks, g_ranks

    # 키워드 클릭시 실시간 검색어 변동을 그려주는 함수
    def draw_keyword_trend(self):
        # (Rank, Time) 형식으로 저장해놓은 2중 리스트를 rank와 time의 리스트로 분리한다
        def split_rank_time(rank_n_time):
            rank = list()
            time = list()
            for i in range(len(rank_n_time)):
                rank.append(rank_n_time[i][0])
                time.append(rank_n_time[i][1])
            return rank, time

        # 사용자가 클릭한 키워드에 대해서 수집한
        # 네이버, 다음, 구글의 (Rank, Times) 데이터 중
        # Times 데이터 중 가장 많은 Time 데이터를 가진 리스트를 반환한다
        # 그래프를 그릴 때, 가장 많은 Time 데이터로 x축을 설정해줘야 하기 때문
        def get_max_times(n_times, d_times, g_times):
            max_times = n_times
            if len(max_times) < len(d_times):
                max_times = d_times
            if len(max_times) < len(g_times):
                max_times = g_times
            return max_times

        # 실시간 검색어에 대한 정보를 종합하여
        # 화면으로 띄워주는 함수
        # 그래프를 그릴 때에 필요한 세세한 항목들을 수행
        def draw(n_ranks, d_ranks, g_ranks, max_times):
            plt.figure(figsize = (10, 5))
            plt.title('실시간 검색어 순위 변동  \'' + self.keyword.text() + '\'')
            if len(n_ranks) != None:
                plt.plot(n_ranks, label='Naver', color='green', linestyle='--', marker='.')
            if len(d_ranks) != None:
                plt.plot(d_ranks, label='Daum', color='brown', linestyle='--', marker='.')
            if len(g_ranks) != None:
                plt.plot(g_ranks, label='Google', color='blue', linestyle='--', marker='.')
            plt.legend()
            plt.ylabel('Rank')
            plt.xlabel('Time')
            plt.ylim([1,11])
            plt.xticks(range(len(max_times)), max_times, rotation=-15)
            plt.yticks(range(11), [''] + [x for x in range(10, 0, -1)])
            plt.show()

        n_ranks_n_times, d_ranks_n_times, g_ranks_n_times = self.get_ranks_times(self.keyword.text())
        n_ranks, n_times = split_rank_time(n_ranks_n_times)
        d_ranks, d_times = split_rank_time(d_ranks_n_times)
        g_ranks, g_times = split_rank_time(g_ranks_n_times)
        max_times = get_max_times(n_times, d_times, g_times)
        draw(n_ranks, d_ranks, g_ranks,  max_times)

# Main Window에서 키워드 클릭시 특정 동작을 위한
# keyword_btn <-> keyword_clicked() 연결
def connect_btn(rank_containers_list, keyword_clicked):
    # 이상하게 for loop로 돌리면 모든 버튼이 맨 왼쪽 아래 버튼으로 연결됨
    # 원인은 찾지 못해서 일단 하드코딩
    # => 찾아볼 것
    rank_containers_list[0][0].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][0]))
    rank_containers_list[0][1].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][1]))
    rank_containers_list[0][2].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][2]))
    rank_containers_list[0][3].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][3]))
    rank_containers_list[0][4].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][4]))
    rank_containers_list[0][5].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][5]))
    rank_containers_list[0][6].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][6]))
    rank_containers_list[0][7].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][7]))
    rank_containers_list[0][8].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][8]))
    rank_containers_list[0][9].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[0][9]))
    rank_containers_list[1][0].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][0]))
    rank_containers_list[1][1].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][1]))
    rank_containers_list[1][2].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][2]))
    rank_containers_list[1][3].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][3]))
    rank_containers_list[1][4].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][4]))
    rank_containers_list[1][5].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][5]))
    rank_containers_list[1][6].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][6]))
    rank_containers_list[1][7].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][7]))
    rank_containers_list[1][8].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][8]))
    rank_containers_list[1][9].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[1][9]))
    rank_containers_list[2][0].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][0]))
    rank_containers_list[2][1].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][1]))
    rank_containers_list[2][2].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][2]))
    rank_containers_list[2][3].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][3]))
    rank_containers_list[2][4].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][4]))
    rank_containers_list[2][5].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][5]))
    rank_containers_list[2][6].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][6]))
    rank_containers_list[2][7].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][7]))
    rank_containers_list[2][8].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][8]))
    rank_containers_list[2][9].clicked.connect(lambda: keyword_clicked(keyword=rank_containers_list[2][9]))