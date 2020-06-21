'''
  -*- coding: utf-8 -*-

  2019 - 2학기 - 정보융합학부 데이터사이언스
  빅데이터 처리 및 응용 강의 지정 프로젝트

  주제 : " 네이버 - 다음 - 구글 실시간 검색어 순위 크롤링 및 분석 "

  Blog : https://blog.naver.com/sooftware
  GitHub : https://github.com/sh951011

  Kwangwoon University Electronic-Communication Dept. 2014707073 김수환

'''

from PyQt5 import QtCore, QtGui, QtWidgets, Qt
from multi import MultiCrawler
from matplotlink import MatplotWidget
from keyword_trend import connect_btn, KeywordTrendWindow
import logging
import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import font_manager, rc
from matplotlib import style
from datetime import datetime
import queue

# MAIN WINDOW ==
MAIN_WINDOW_WIDTH = 1280
MAIN_WINDOW_HEIGHT = 1000
RANK_NUM = 10
# ==========================

# TITLE ==
TITLE_COORD_X = 160
TITLE_COORD_Y = 25
TITLE_WIDTH = 1000
TITLE_HEIGHT = 50
MIDDLE_COORD_Y = 410
MIDDLE_WIDTH = 300
MIDDLE_HEIGHT = TITLE_HEIGHT
MIDDLE1_COORD_X = 85
MIDDLE2_COORD_X = 265
MIDDLE3_COORD_X = 640
MIDDLE4_COORD_X = 1010
# ==========================

# RANK CONTAINERS ==
RANK_WIDTH = 350
RANK_HEIGHT = 30
RANK_COORD_X = 150
RANK_COORD_Y = 485
RANK_GAP_X = 380
RANK_GAP_Y = 50
SHOW_RANK_WIDTH = 60
SHOW_RANK_HEIGHT = RANK_HEIGHT
# ==========================

# CORR ==
CORR_COORD_X = 180
CORR_COORD_Y = 365
CORR_WIDTH = 80
CORR_HEIGHT = 30
# =========================

# TIME ==
TIME_COORD_X = 50
TIME_COORD_Y = CORR_COORD_Y
TIME_WIDTH = 380
TIME_HEIGHT = CORR_HEIGHT
# =========================

# MATPLOT ==
PLOT_COORD_X = 50
PLOT_COORD_Y = 90
PLOT_GAP_X = 420
PLOT_WIDTH = TIME_WIDTH
PLOT_HEIGHT = 270
PLOT_COMMENT_COORD_X = 545
PLOT_COMMENT_GAP_X = 90
PLOT_COMMENT_COORD_Y = TIME_COORD_Y
PLOT_COMMENT_WIDTH = 70
PLOT_COMMENT_HEIGHT = TIME_HEIGHT
# ==========================

# KEYWORD ==
KEYWORD_HEIGHT = 25
KEYWORD_WIDTH = PLOT_WIDTH
KEYWORD_COORD_X = PLOT_COORD_X + 2 * PLOT_GAP_X
KEYWORD_COORD_Y = 105
KEYWORD_GAP_Y = 43
# =========================

# FONT ==
MARGUN_FONT = "맑은 고딕"
ARIAL_BLACK_FONT = "Arial Black"
ARIAL_FONT = "Arial"
TITLE_FONT_SIZE = 24
MEDIUM_FONT_SIZE = 14
RANK_FONT_SIZE = 12
# ==========================

# Basic Setting ==
logger = logging.getLogger('root')
FORMAT = "[%(asctime)s %(filename)s:%(lineno)s - %(funcName)s()] %(message)s"
logging.basicConfig(stream=sys.stdout, level=logging.DEBUG, format=FORMAT)
logger.setLevel(logging.INFO)
font_name = font_manager.FontProperties(fname="c:/Windows/Fonts/malgun.ttf").get_name()
rc('font', family=font_name)
style.use('ggplot')
# ==========================

class MainWindow(object):
    def __init__(self):
        self.main_window = None
        self.centralwidget = None
        self.queue = queue.Queue(3)  # Multi Threading을 위한 큐
        self.data_list = list()  # 크롤링한 데이터들을 합친 리스트
        self.n_ranks = None  # Naver 검색어 저장
        self.d_ranks = None  # Daum 검색어 저장
        self.g_ranks = None  # Google 검색어 저장
        self.rank_containers_list = None
        self.case = 'Naver-Daum'

        # 정수만을 입력받기 위한 처리
        while True:
            self.update_period = input("Enter Update Peroid (sec) : ")
            if self.update_period.isdecimal():
                break

    def setup(self, main_window):
        # Main_Window Set ===
        translate = QtCore.QCoreApplication.translate
        main_window.resize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)
        main_window.setMinimumSize(QtCore.QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT))
        self.centralwidget = QtWidgets.QWidget(main_window)
        main_window.setWindowTitle(translate("MainWindow", "Naver Daum Google Search Ranking"))
        # ============================================

        # Matplot ===
        # - corr, time, donut chart, color denote
        self.keywords_score = MatplotWidget(self.centralwidget)
        self.keywords_score.setGeometry(QtCore.QRect(PLOT_COORD_X + PLOT_GAP_X, PLOT_COORD_Y, PLOT_WIDTH, PLOT_HEIGHT))
        self.corr = MatplotWidget(self.centralwidget)
        self.corr.setGeometry(QtCore.QRect(PLOT_COORD_X, PLOT_COORD_Y, PLOT_WIDTH, PLOT_HEIGHT))
        denote_colors = ['#c2c2f0', '#ff9999', '#ffb3e6']
        denote_text = ['Naver','Daum','Google']
        self.color_denote = [0] * 3
        for i, label in enumerate(self.color_denote):
            label = QtWidgets.QLabel(self.centralwidget)
            label.setGeometry(QtCore.QRect(PLOT_COMMENT_COORD_X + i * PLOT_COMMENT_GAP_X, TIME_COORD_Y, PLOT_COMMENT_WIDTH, TIME_HEIGHT))
            font = QtGui.QFont(ARIAL_BLACK_FONT)
            font.setPointSize(11)
            label.setFont(font)
            label.setAlignment(QtCore.Qt.AlignCenter)
            label.setStyleSheet("color: " + denote_colors[i] + ";")
            label.setText(denote_text[i])
        # ============================================

        # Title ===
        # - Naver - Daum - Google 실시간 검색어 순위
        self.title = QtWidgets.QLabel(self.centralwidget)
        self.title.setGeometry(QtCore.QRect(TITLE_COORD_X, TITLE_COORD_Y, TITLE_WIDTH, TITLE_HEIGHT))
        font = QtGui.QFont(ARIAL_BLACK_FONT)
        font.setPointSize(TITLE_FONT_SIZE)
        self.title.setFont(font)
        self.title.setAlignment(QtCore.Qt.AlignCenter)
        self.title.setText(translate("MainWindow", "Naver - Daum - Google  실시간 검색어 순위"))
        self.title.setStyleSheet("color: purple;")
        # =============================

        # Time ===
        now = datetime.now()
        time = str(now.year)
        format_ = [now.month, now.day, now.hour, now.minute]
        delimiters = ['-', '-', ' ', ':']
        for i, item in enumerate(format_):
            time += delimiters[i] + str(item)
        self.time_plot = QtWidgets.QLabel(self.centralwidget)
        self.time_plot.setGeometry(QtCore.QRect(TIME_COORD_X, TIME_COORD_Y, TIME_WIDTH, TIME_HEIGHT))
        font = QtGui.QFont(MARGUN_FONT)
        font.setPointSize(12)
        self.time_plot.setFont(font)
        self.time_plot.setAlignment(QtCore.Qt.AlignCenter)
        self.time_plot.setText(translate("MainWindow", "<"+time+"> 기준"))
        # ============================

        # Middle ===
        # - 순위, Naver, Daum, Google 표시
        labels = ['순위', 'Naver', 'Daum', 'Google']
        colors = ['black', 'green', 'brown', 'blue']
        geometrys = [
            [MIDDLE1_COORD_X, MIDDLE_COORD_Y, MIDDLE_WIDTH, MIDDLE_HEIGHT],
            [MIDDLE2_COORD_X, MIDDLE_COORD_Y, MIDDLE_WIDTH, MIDDLE_HEIGHT],
            [MIDDLE3_COORD_X, MIDDLE_COORD_Y, MIDDLE_WIDTH, MIDDLE_HEIGHT],
            [MIDDLE4_COORD_X, MIDDLE_COORD_Y, MIDDLE_WIDTH, MIDDLE_HEIGHT]
        ]
        fonts = [MARGUN_FONT] + [ARIAL_BLACK_FONT] * 3
        font_sizes = [MEDIUM_FONT_SIZE] + [TITLE_FONT_SIZE] * 3

        for i in range(4):
            self.middle = QtWidgets.QLabel(self.centralwidget)
            self.middle.setGeometry(QtCore.QRect(geometrys[i][0], geometrys[i][1], geometrys[i][2], geometrys[i][3]))
            font = QtGui.QFont(fonts[i])
            font.setPointSize(font_sizes[i])
            self.middle.setFont(font)
            self.middle.setText(translate("MainWindow", labels[i]))
            self.middle.setStyleSheet("color: " + colors[i] + ";")
        # ===========================

        # Keyword Label ===
        # Naver - Daum, Daum - Google, Google - Naver 의 max distance, min distance 표시해주는 부분
        self.max_keyword_label = [0] * 3
        self.min_keyword_label = [0] * 3
        blue_font = QtGui.QFont(ARIAL_BLACK_FONT)
        blue_font.setPointSize(13)
        black_font = QtGui.QFont(ARIAL_BLACK_FONT)
        black_font.setPointSize(12)
        for i in range(3):
            self.max_keyword_label[i] = QtWidgets.QLabel(self.centralwidget)
            self.max_keyword_label[i].setGeometry(QtCore.QRect(KEYWORD_COORD_X,KEYWORD_COORD_Y + 2 * i * KEYWORD_GAP_Y,KEYWORD_WIDTH,KEYWORD_HEIGHT))
            self.max_keyword_label[i].setFont(blue_font)
            self.max_keyword_label[i].setAlignment(QtCore.Qt.AlignCenter)
            self.max_keyword_label[i].setStyleSheet("color: blue;")
            self.min_keyword_label[i] = QtWidgets.QLabel(self.centralwidget)
            self.min_keyword_label[i].setGeometry(QtCore.QRect(KEYWORD_COORD_X,KEYWORD_COORD_Y + KEYWORD_GAP_Y + 2 * i * KEYWORD_GAP_Y,KEYWORD_WIDTH,KEYWORD_HEIGHT))
            self.min_keyword_label[i].setFont(black_font)
            self.min_keyword_label[i].setAlignment(QtCore.Qt.AlignCenter)
            self.min_keyword_label[i].setStyleSheet("color: black;")
        self.keyword_comment = QtWidgets.QLabel(self.centralwidget)
        self.keyword_comment.setGeometry(QtCore.QRect(KEYWORD_COORD_X, CORR_COORD_Y, KEYWORD_WIDTH, KEYWORD_HEIGHT))
        font = QtGui.QFont(MARGUN_FONT)
        font.setPointSize(11)
        self.keyword_comment.setFont(font)
        self.keyword_comment.setAlignment(QtCore.Qt.AlignCenter)
        # ============================

        # Rank Containers ===
        # - 각 포털 검색어 1 - 10위를 표시하는 부분
        def _create_rank_containers(self):
            self.rank_containers_list = [[] for x in range(3)]

            for i, rank_containers in enumerate(self.rank_containers_list):
                for j in range(RANK_NUM):
                    rank_containers.append(QtWidgets.QPushButton(self.centralwidget))
                for j, rank in enumerate(rank_containers):
                    rank.setGeometry(QtCore.QRect(RANK_COORD_X + RANK_GAP_X * i,
                                                  RANK_COORD_Y + RANK_GAP_Y * j,
                                                  RANK_WIDTH, RANK_HEIGHT))
                    font = QtGui.QFont(MARGUN_FONT)
                    font.setPointSize(RANK_FONT_SIZE)
                    rank.setFont(font)
                    rank.setStyleSheet("border-radius: 5px;\n""color: black;\n")

            for i in range(10):
                rank_label = QtWidgets.QLabel(self.centralwidget)
                rank_label.setGeometry(QtCore.QRect(MIDDLE1_COORD_X, RANK_COORD_Y + RANK_GAP_Y * i, SHOW_RANK_WIDTH, SHOW_RANK_HEIGHT))
                font = QtGui.QFont(ARIAL_FONT)
                font.setPointSize(MEDIUM_FONT_SIZE)
                rank_label.setFont(font)
                rank_label.setObjectName("rank_label" + str(i))
                rank_label.setText(translate("MainWindow", " "  + str(i+1) + "위"))
        # ================================================

        # Event Connect
        def _set_connect(self):
            self.crawling()  # 처음 실행시 크롤링 실행
            self.update_corrs()  # 처음 실행시 Naver - Daum 상관관계 plot
            connect_btn(self.rank_containers_list, self.keyword_clicked)  # 각 검색어 버튼들 keyword_clicked와 연결
            self.crawling_timer = QtCore.QTimer()  # 타이머 설정
            self.crawling_timer.setInterval(1000 * int(self.update_period))  # ms단위라 1000과 입력받은 주기 (sec)을 곱해주면 해당 초만큼 주기적으로 실행
            self.corr_timer = QtCore.QTimer()  # 타이머 설정
            self.corr_timer.setInterval(1000 * 20)  # 20초 단위로 네이버 - 다음, 다음 - 구글, 구글 - 네이버 상관관계 그리도록 설정
            self.crawling_timer.timeout.connect(self.crawling)
            self.crawling_timer.start()
            self.corr_timer.timeout.connect(lambda: self.update_corrs())
            self.corr_timer.start()

        _create_rank_containers(self)
        _set_connect(self)
        main_window.setCentralWidget(self.centralwidget)


    # 키워드 클릭시 실행
    def keyword_clicked(self, keyword):
        rank_changes = KeywordTrendWindow(keyword=keyword)
        rank_changes.show()

        # 상관관계
    def update_corrs(self):
        # ranks1과 ranks2의 상관관계 계산
        # 순위 1-10위까지만을 이용하여 비교를 하고,
        # 매치되지 않는 키워드들도 있으므로 기존 상관관계 계산법에 따르지 않고 새로 정의
        # 상관관계는 보통 -1.0 ~ 1.0 의 값을 가지지만, 검색어 순위의 상관관계에서
        # 음의 상관관계는 나올 수가 없다고 판단하고, 0.0 ~ 1.0 으로 제한을 둠
        # 계산시, N사 1등과 D사 10등이 있다고 하면, 기존 상관관계 계산법으로는 낮은 상관관계가 나오겠지만,
        # 검색어 10위라는 값이 이미 어느 정도 상관관계가 있다고 판단하여, 통상적으로 강한 상관관계라고 판단하기 시작하는 0.3의 값을 부여해줌.
        def _get_corrs(ranks1, ranks2):
            ranks1.reverse()
            ranks2.reverse()
            corrs = list()

            for i, keyword1 in enumerate(ranks1):
                corrs.append(0)
                for j, keyword2 in enumerate(ranks2):
                    if keyword1 == keyword2:
                        # 순위가 같다면 corr == 1
                        # 랭킹에 있는데 순위가 다르다면
                        # Naver는 1위 Daum은 10위라고 한다면, 둘이 상관관계가 어느 정도 있다고 판단하고
                        # 통상적으로 어느 정도 상관관계가 있다고 판단하는 0.3을 준다
                        # 그 사이의 값들은 0.3 ~ 1.0 까지 중 distance 를 고려하여 corr을 계산한다
                        corrs[i] = 1.0 if i == j else ( 1 - (0.7 / 9) * abs(i - j) )
                        break
            return corrs

        # get_corrs로 계산한 corr들을 plot
        def _draw(self, corrs, engine1='Naver', engine2='Daum'):
            self.corr.canvas.axes.clear()
            self.corr.canvas.axes.scatter([str(x) for x in range(10)], corrs, color='lightcoral', label = "corr " + str(round(np.mean(corrs),2)))
            self.corr.canvas.axes.legend(fontsize='medium', loc='upper left')
            self.corr.canvas.axes.set_xticklabels(['Rank10', '.', '.', '.', '.', '.', '.', '.', '.', 'Rank1'])
            self.corr.canvas.axes.set_title(engine1 + ' - ' + engine2  + ' corr')
            self.corr.canvas.axes.set_ylim([-0.1, 1.1])
            self.corr.canvas.axes.grid(linewidth=0.2)
            self.corr.canvas.draw()

        case = ['Naver-Daum','Daum-Google','Google-Naver']
        ranks_pair = [[self.n_ranks, self.d_ranks],
                      [self.d_ranks, self.g_ranks],
                      [self.g_ranks, self.n_ranks]]
        index = case.index(self.case)
        corrs = _get_corrs(ranks_pair[index][0], ranks_pair[index][1])
        _draw(self, corrs, engine1=self.case.split('-')[0], engine2=self.case.split('-')[1])
        self.case = case[(index + 1) % 3]  # index가 0 1 2 가 반복되면서 돌도록 설정

    # 크롤링
    def crawling(self):
        # Naver - Daum - Google에서 수집한 검색어 순위를 포맷에 맞춰 csv 파일로 저장
        def update_data(self):
            columns = ['Time', 'Search Engine']
            columns += ['Rank' + str(i) for i in range(1, 11)]
            data_list = list()

            for i in range(3):
                data_list += self.queue.get() # Thread들이 저장해놓은 데이터 get

            self.data_list = data_list

            new_data = pd.DataFrame(np.array(data_list).reshape(3, 12), columns=columns) # 새로 수집한 데이터
            read_data = pd.read_csv('./data/data.csv', encoding='utf-8') # 기존 엑셀 파일 데이터
            merge_data = pd.concat([read_data, new_data], sort=False) # (기존 + New) 병합
            merge_data.to_csv('./data/data.csv', encoding='utf-8', sep=',', index=False) # 병합 데이터 저장

        # 검색어 종합 스코어 Top5를 donut chart로 표시
        # - 3포털에 대해서 점수를 합산해서 상위 스코어 5개를 표시한다
        # - Top5 키워드에서 어느 포털에서 해당 키워드 점수를 많이 차지했는지는 sunplot으로 표시한다
        def update_donut(self):
            # 각 키워드별로 점수 계산
            # 각 포털 1위는 10점 2위는 9점 ... 10위는 1점 순위권 밖은 0점을 준다
            def _get_keywords_score(self):
                scores = []  # 키워드에 대한 점수를 저장하는 리스트
                except_case = [0,1,12,13,24,25] # csv파일의 'Time', 'Search Engine' 컬럼에 해당하는 인덱스는 예외처리
                keywords = []  # 키워드를 저장하는 리스트
                k = 0
                self.g_ranks = self.data_list[2:12]  # google 검색어 저장
                self.n_ranks = self.data_list[14:24]  # Naver 검색어 저장
                self.d_ranks = self.data_list[26:36]  # Daum 검색어 저장

                # self.data_list (3 포털 검색어가 저장된 리스트) 에서 키워드를 하나씩 뽑는다
                for i, keyword in enumerate(self.data_list):
                    if i in except_case: # 미리 선언해놓은 except_case면 건너뛴다
                        continue
                    score = 10 - ( k % 10 )  # score가 10 ~ 1점이 나오도록 한다 => score는 총 30개가 나오는데 10 9 ... 1이 3번 반복된다
                    k += 1
                    # keywords에 keyword가 없다면 새로 삽입과, score를 계산한다(
                    if keyword not in keywords:
                        keywords.append(keyword)
                        scores.append(score)
                    # keywords에 keyword가 있다면 (다른 포털 keyword와 일치하는 경우)
                    # 해당 keyword의 index를 계산하여 점수를 더해준다
                    else:
                        index = keywords.index(keyword)
                        scores[index] += (score)

                scores, keywords = zip(*sorted(zip(scores, keywords), reverse = True)) # sort together (scores를 기준으로 keywords도 같이 정렬)
                return keywords, scores

            # 각 포털의 Top5 키워드의 점수 계산
            def _top5_engines_score(self, keywords):
                g_scores = [10 - self.g_ranks.index(keyword) if keyword in self.g_ranks else 0 for keyword in keywords]
                n_scores = [10 - self.n_ranks.index(keyword) if keyword in self.n_ranks else 0 for keyword in keywords]
                d_scores = [10 - self.d_ranks.index(keyword) if keyword in self.d_ranks else 0 for keyword in keywords]

                return n_scores, d_scores, g_scores

            # get_keywords_score로 계산한 Top5를 도넛 차트로 draw
            def _draw(self, keywords, scores, n_scores, d_scores, g_scores):
                explode = [0.07] * 5
                outer_colors = ['#ff6666', '#ffcc99', '#99ff99', '#66b3ff', 'skyblue']
                inner_colors = ['#c2c2f0', '#ff9999', '#ffb3e6'] * 5
                site_ratio = list()

                for i in range(5):
                    site_ratio.extend([n_scores[i],d_scores[i],g_scores[i]])

                self.keywords_score.canvas.axes.clear()
                self.keywords_score.canvas.axes.pie(scores, labels=keywords, shadow=True, startangle=90, colors = outer_colors, explode = explode)
                self.keywords_score.canvas.axes.pie(site_ratio, shadow=True, radius=0.65, startangle=90, colors = inner_colors, explode = explode * 3)
                circle = plt.Circle((0, 0), 0.5, color='white')
                self.keywords_score.canvas.axes.add_artist(circle)
                self.keywords_score.canvas.axes.set_title("종합 검색어 스코어 Top 5")
                self.keywords_score.canvas.axes.grid(linewidth=0.2)
                self.keywords_score.canvas.draw()

            keywords, scores = _get_keywords_score(self)
            n_scores, d_scores, g_scores = _top5_engines_score(self, keywords)
            _draw(self, keywords[:5], scores[:5], n_scores, d_scores, g_scores)

        # 1 - 10위까지 키워드 중 순위 차이가 가장 큰 키워드와 작은 키워드 표시
        def update_keywords(self,ranks1, ranks2,engine1,engine2,loc = 0):
            # 1 - 10위까지 키워드들 중에 중복되는 키워드들의 distance를 계산
            def _get_distances(self, ranks1, ranks2):
                # 중복되는 키워드를 추출
                def _extract_keywords(self, ranks1, ranks2):
                    keywords = list()
                    for item in ranks1:
                        if item in ranks2:
                            keywords.append(item)
                    return keywords
                # 중복 키워드들의 distance 계산
                def _cal_distance(self, keywords, ranks1, ranks2):
                    distances = list()
                    for keyword in keywords:
                        distances.append(abs(ranks1.index(keyword) - ranks2.index(keyword)))
                    return distances

                keywords = _extract_keywords(self, ranks1=ranks1, ranks2=ranks2)
                distances = _cal_distance(self, keywords=keywords,ranks1=ranks1,ranks2=ranks2)

                return keywords, distances

            # get_distances()로 계산한 distance 기준으로 키워드 Set
            def _set_keywords(self, keywords, distances, engine1, engine2, loc = 0):
                # 계산한 distance 기준으로 max_corr, min_corr을 계산
                def _get_max_n_min_corr(keywords, distances):
                    # 중복되는 키워드가 없는 경우 '해당없음'으로 표시
                    if len(distances) == 0:
                        return '해당없음', '해당없음'
                    # distance가 가장 작은 키워드가 max_corr, distance가 가장 큰 키워드가 min_corr
                    return keywords[(distances.index(min(distances)))], keywords[(distances.index(max(distances)))]

                # max_corr, min_corr 키워드 Set
                # 추가로 현재시간 업데이트도 같이 함
                def _set_text(self, max_corr_keyword, min_corr_keyword, engine1, engine2, loc):
                    translate = QtCore.QCoreApplication.translate
                    self.max_keyword_label[loc].setText(translate("MainWindow", engine1 + " - " + engine2 + " " + max_corr_keyword))
                    self.min_keyword_label[loc].setText(translate("MainWindow", engine1 + " - " + engine2 + " " + min_corr_keyword))
                    self.keyword_comment.setText(translate("MainWindow", "blue : min distance   black : max distance"))
                    now = datetime.now()
                    time = str(now.year)
                    format_ = [now.month, now.day, now.hour, now.minute]
                    delimiters = ['-', '-', ' ', ':']
                    for i, item in enumerate(format_):
                        time += delimiters[i] + str(item)
                    self.time_plot.setText(translate("MainWindow", "<" + time + "> 기준"))

                max_corr_keyword, min_corr_keyword = _get_max_n_min_corr(keywords, distances)
                _set_text(self, max_corr_keyword, min_corr_keyword, engine1=engine1, engine2=engine2, loc=loc)

            keywords, distances = _get_distances(self, ranks1=ranks1,ranks2=ranks2)
            _set_keywords(self, keywords=keywords,distances=distances,engine1=engine1,engine2=engine2, loc=loc)

        # web_crawling Func Execute code
        multi_crawler = MultiCrawler(self.rank_containers_list, self.queue) # Multi Threading Crawling
        multi_crawler.start() # Multi Thread Run
        multi_crawler.join()  # Wait Threads
        update_data(self)
        update_donut(self)
        engine_list = [['Naver', 'Daum'], ['Daum', 'Google'], ['Google', 'Naver']]
        self.g_ranks.reverse()  # 왜 g_ranks가 뒤집어져 있는지 아직 확인 못함
        ranks_list = [[self.n_ranks, self.d_ranks], [self.d_ranks, self.g_ranks], [self.g_ranks, self.n_ranks]]
        for i in range(3):
            update_keywords(self, ranks1=ranks_list[i][0], ranks2=ranks_list[i][1], engine1=engine_list[i][0], engine2=engine_list[i][1], loc = i)

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    main_window = QtWidgets.QMainWindow()
    process = MainWindow()
    process.setup(main_window)
    main_window.show()
    sys.exit(app.exec_())