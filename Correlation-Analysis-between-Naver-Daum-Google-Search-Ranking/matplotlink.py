'''
  -*- coding: utf-8 -*-

  Matplotlib와 PyQt5의 연동을 위한 기본 설정을 해주는 기능 구현

  Blog : https://blog.naver.com/sooftware
  GitHub : https://github.com/sh951011

'''

from PyQt5.QtWidgets import*
from matplotlib.backends.backend_qt5agg import FigureCanvas
from matplotlib.figure import Figure


class MatplotWidget(QWidget):
    def __init__(self, parent = None):
        QWidget.__init__(self, parent)        
        self.canvas = FigureCanvas(Figure())
        vertical_layout = QVBoxLayout()
        vertical_layout.addWidget(self.canvas)        
        self.canvas.axes = self.canvas.figure.add_subplot(111)
        self.setLayout(vertical_layout)

