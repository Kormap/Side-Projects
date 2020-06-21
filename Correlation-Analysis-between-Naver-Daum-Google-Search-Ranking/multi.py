'''
  -*- coding: utf-8 -*-
  네이버 - 다음 - 구글 실시간 검색어 크롤링 기능 구현
  멀티스레딩 기법 사용
  Blog : https://blog.naver.com/sooftware
  GitHub : https://github.com/sh951011
'''

import threading
import sys
import logging
from urllib.request import urlopen
from bs4 import BeautifulSoup
from datetime import datetime
from selenium import webdriver
from PyQt5 import QtCore

# Basic Setting ==
logger = logging.getLogger('root')
FORMAT = "[%(asctime)s %(filename)s:%(lineno)s - %(funcName)s()] %(message)s"
logging.basicConfig(stream=sys.stdout, level=logging.DEBUG, format=FORMAT)
logger.setLevel(logging.INFO)
chrome_driver = webdriver.Chrome('./driver/chromedriver')
chrome_driver.get('https://trends.google.co.kr/trends/trendingsearches/daily?geo=KR')
# ====================================

# Multi Crawling Using Thread
class MultiCrawler():
    def __init__(self, rank_containers_list, queue):
        self.threads = list()  # Crawler thread를 저장할 리스트
        self.queue = queue     # thread 꼬임 방지용 큐
        search_engines = ['Naver', 'Daum', 'Google']  # 검색엔진 리스트

        for i, search_engine in enumerate(search_engines):
            self.threads.append(Crawler(search_engine, rank_containers_list[i], self.queue))

    # Thread Run
    def start(self):
        for thread in self.threads:
            thread.start()

    # Thread Join
    def join(self):
        for thread in self.threads:
            thread.join()

class Crawler(threading.Thread):
    def __init__(self, search_engine, rank_containers, queue):
        super(Crawler, self).__init__()
        self.search_engine = search_engine
        if self.search_engine.lower() == 'naver':
            self.url = 'https://www.naver.com'
            self.html = urlopen(self.url)
        elif self.search_engine.lower() == 'daum':
            self.url = 'https://www.daum.net'
            self.html = urlopen(self.url)
        elif self.search_engine.lower() == 'google':
            self.xpath = """/html/body/div[2]/div[2]/div/div[2]"""
            self.driver = chrome_driver
            self.driver.find_element_by_xpath(self.xpath)
            self.html = self.driver.page_source
        else:
            logger.info("class Crawler __init__ : not matching search_engine")
            exit(0)

        self.soup = BeautifulSoup(self.html, "html.parser")
        self.rank_containers = rank_containers
        self.data_list = None
        self.queue = queue

    def run(self):
        def crawling(self):
            search_word_list = []
            now = datetime.now()
            delimiters = ['-', '-', ' ', ':']
            time = str(now.year)
            format_ = [now.month, now.day, now.hour, now.minute]
            for i, item in enumerate(format_):
                time += delimiters[i] + str(item)

            # 네이버 검색어 순위 크롤링
            if self.search_engine.lower() == 'naver':
                for i in range(10):
                    search_word_list.append(self.soup.find_all('li', 'ah_item')[i].find(class_='ah_k').get_text())
            # 다음 검색어 순위 크롤링
            elif self.search_engine.lower() == 'daum':
                for i in range(10):
                    search_word_list.append(self.soup.find_all('span', 'txt_issue')[2 * i].get_text())
            # 구글 검색어 순위 크롤링
            elif self.search_engine.lower() == 'google':
                rank_html = self.soup.find_all('div', 'details-top')
                for i in range(10):
                    search_word_list.append(rank_html[i].find(class_='title').get_text().strip())
            else:
                logger.info("class Crawler run : not matching search_engine")
                exit(0)


            for i, search_word in enumerate(search_word_list):
                logger.info(self.search_engine + " "  + str(i + 1) + " " + search_word)

            self.data_list = search_word_list
            contents = [time] + [self.search_engine] + self.data_list  # format : Time  Search_Engine  Rank1  Rank2  ...  Rank10
            self.queue.put(contents)

        def set_text(self):
            for i, container in enumerate(self.rank_containers):
               translate = QtCore.QCoreApplication.translate
               container.setText(translate("MainWindow", self.data_list[i]))

        crawling(self)
        set_text(self)