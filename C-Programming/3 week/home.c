/*
2014707073 김수환
소프트웨어설계 5주차 과제
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define random() (float)rand()/RAND_MAX         
#define RAND() ((float)rand()/(RAND_MAX))*32300      

/*
rand함수를 RAND_MAX로 나눠줌으로써 0~1까지의 값을 갖게한다
rand함수를 RAND_MAX로 나눠주고 32300을 곱해준다
rand함수는 0~32367까지의 값을 가지는데, 100으로 나눠준 나머지의 값+1로
1~100의 숫자를 채우려고 하면 32301~32367의 나머지인 1~67까지의 나머지가 한번씩 더 들어가게 되므로 확률이 공정치 못하다.
그러므로 0~32300까지의 숫자가 찍히게 하기위한 define
*/

int generate_array();
int evaluate_array();
int select_array();
int cross_array();
int transition_array();
void copy_array();
void recursion();
void print_array();

// 사용할 함수들을 선언해준다

struct arr {
   int arr1[10];
   int arr2[10];
   int arr3[10];
   int arr4[10];
   int arr5[10];
   int arr6[10];
   int arr7[10];
   int arr8[10];
   int arr[10];
}arr;

struct score {
   float score[8];
   float score2[8];
   float score3[8];
   int total_score;
}score;

struct choice {
   int choice[40];
   int choice1[10], choice2[10], choice3[10], choice4[10];
}choice;

struct cross {
   int cross1[10], cross2[10], cross3[10], cross4[10];
   int cross5[10], cross6[10], cross7[10], cross8[10];
}cross;

struct arr arr;
struct score score;
struct choice choice;
struct cross cross;

// 사용할 구조체를 선언해준다

void main() {
   srand((unsigned)time(NULL));
   generate_array(&arr);
   evaluate_array(&arr, &score);
   select_array(&arr, &score, &choice);
   recursion(&arr, &score);
   print_array(&arr);
}

/*
rand함수의 경우 일정한 알고리즘을 가지고 숫자를 뽑기 때문에, 숫자가 나오는 순서가 똑같다.
그러므로, 시행할때마다 다른 숫자가 나오게 하기 위해 srand함수를 사용한다.
srand함수의 경우 프로그램 실행자가 프로그램 실행하는 시간을 seed로 받아 rand함수의 결과값이 바뀌게 해준다.
사용자의 시간을 srand에서 활용하기 위해 #include <time.h>를 해준다

교차와 변이와 평가 같은 함수의 경우 반복적으로 실행을 해줘야 하는데 main함수를 간단하게 만들기 위해
recursion이라는 함수를 새로 만들어 교차 변이 평가를 반복적으로 해주는 함수를 만들었다.

print_array는 최종 결과 배열을 출력하는 함수이다.
*/

int generate_array(struct arr *x) { // 배열 생성
   int i = 0;
   for (i = 0; i<10; i++) {
      x->arr1[i] = (int)(RAND()) % 100 + 1; // 위에서 선언해준 RAND함수를 100으로 나눈 나머지
      x->arr2[i] = (int)(RAND()) % 100 + 1; // 의 값에 1을 해줌으로써 1~100이 찍히게 해준다.
      x->arr3[i] = (int)(RAND()) % 100 + 1;
      x->arr4[i] = (int)(RAND()) % 100 + 1;
      x->arr5[i] = (int)(RAND()) % 100 + 1;
      x->arr6[i] = (int)(RAND()) % 100 + 1;
      x->arr7[i] = (int)(RAND()) % 100 + 1;
      x->arr8[i] = (int)(RAND()) % 100 + 1;
   }
}

int evaluate_array(struct arr *x, struct score *y) { // 규칙1 평가
   int i = 0;

   for (i = 0; i<8; i++) {
      y->score[i] = 0;
      y->score2[i] = 0;
      y->score3[i] = 0;
   }
   y->total_score = 0;

   // 전의 score구조체가 결과값에 영향을 주지 않게 0으로 초기화해준다

   for (i = 0; i<9; i++) {         // 각 배열들을 오른쪽의 값과 비교해서 오른쪽의
      if ((x->arr1[i])<(x->arr1[i + 1])) {     // 값이 크면 score가 +1이 되도록한다
         (y->score[0]) += 1;
      }
   }

   for (i = 0; i<9; i++) {
      if ((x->arr2[i])<(x->arr2[i + 1])) {
         (y->score[1]) += 1;
      }
   }

   for (i = 0; i<9; i++) {
      if ((x->arr3[i])<(x->arr3[i + 1])) {
         (y->score[2]) += 1;
      }
   }

   for (i = 0; i<9; i++) {
      if ((x->arr4[i])<(x->arr4[i + 1])) {
         (y->score[3]) += 1;
      }
   }

   for (i = 0; i<9; i++) {
      if ((x->arr5[i])<(x->arr5[i + 1])) {
         (y->score[4]) += 1;
      }
   }

   for (i = 0; i<9; i++) {
      if ((x->arr6[i])<(x->arr6[i + 1])) {
         (y->score[5]) += 1;
      }
   }

   for (i = 0; i<9; i++) {
      if ((x->arr7[i])<(x->arr7[i + 1])) {
         (y->score[6]) += 1;
      }
   }

   for (i = 0; i<9; i++) {
      if ((x->arr8[i])<(x->arr8[i + 1])) {
         (y->score[7]) += 1;
      }
   }

   for (i = 0; i<8; i++) {
      (y->total_score) = (y->total_score) + (y->score[i]);
   } // 총 점수를 계산한다
}

int select_array(struct arr *x, struct score *y, struct choice *z) { // 규칙2 선택
   int i = 0, j = 0, n = 0, k = 0;
   float prob = 0;
   int overlap[8] = { 0 };
   int count = 0;

   for (i = 0; i<10; i++) {
      z->choice1[i] = 0;
      z->choice2[i] = 0;
      z->choice3[i] = 0;
      z->choice4[i] = 0;
   }
   for (i = 0; i<40; i++) {
      z->choice[i] = 0;
   }

   // choice 구조체를 초기화해준다

   for (i = 0; i<8; i++) {  // score2에 각 점수 / 총 점수 의 값을 넣어준다.
      (y->score2[i]) = (y->score[i]) / (y->total_score);
   }

   (y->score3[0]) = (y->score2[0]); // score3[0]에는 score2[0]의 값을 일단 넣어준다.
   for (i = 0; i<7; i++) {
      (y->score3[i + 1]) = (y->score3[i]) + (y->score2[i + 1]); // score3에는 순서대로 score2의 합들을 넣어준다
   }   // 즉 score3의 총 합은 1이되도록 한다.

   while (count<4) {   // count변수가 4가되면 while문을 빠져나온다
      count = 0;
      prob = random();   // 0~1의 값을 가질 변수

                     /*
                     score3에는 순서대로 각 점수 / 총점수 의 합들이 들어가있다.
                     ex) 첫번째 배열이 4/20 두번째 배열이 3/20이라면
                     score3[0]dpsms 4/20, score3[1]에는 7/20이 들어가있다.

                     그러므로 prob변수가 0~1의 범위에서 각 값들의 사이 값(0,1포함)에 포함되면
                     choice라는 배열에 선택되도록 한다.
                     그렇게 해서 각 각 배열들을 자신이 가진 배열의 점수 / 각배열의 총점수 의 확률로 선택되도록
                     한다.
                     그리고 그 배열이 중복으로 뽑히는 것을 방지하기 위해
                     overlap라는 변수를 이용해서 이미 한번 뽑힌 배열일 경우 overlap에 값의 변화를 줘서
                     이미 한번 뽑힌 배열이 다시 선택될 경우 while문이 다시 돌도록 설정
                     그리고 overlap이 1이되면 그게 선택된 배열의 숫자를 의미하므로
                     for문을 돌려 overlap[i[배열이 1일 경우 count변수가 ++가 되도록 하여 count=4
                     즉, 4개의 배열이 선택되면 while문을 빠져나가도록 한다.
                     */

      if (prob >= 0 && prob<(y->score3[0]) && overlap[0] == 0) {
         for (j = 0; j<10; j++) {
            z->choice[n] = x->arr1[j];
            n++;
         }
         overlap[0] = 1;
      }
      if (prob >= (y->score3[0]) && prob<(y->score3[1]) && overlap[1] == 0) {
         for (j = 0; j<10; j++) {
            z->choice[n] = x->arr2[j];
            n++;
         }
         overlap[1] = 1;
      }
      if (prob >= (y->score3[1]) && prob<(y->score3[2]) && overlap[2] == 0) {
         for (j = 0; j<10; j++) {
            z->choice[n] = x->arr3[j];
            n++;
         }
         overlap[2] = 1;
      }
      if (prob >= (y->score3[2]) && prob<(y->score3[3]) && overlap[3] == 0) {
         for (j = 0; j<10; j++) {
            z->choice[n] = x->arr4[j];
            n++;
         }
         overlap[3] = 1;
      }
      if (prob >= (y->score3[3]) && prob<(y->score3[4]) && overlap[4] == 0) {
         for (j = 0; j<10; j++) {
            z->choice[n] = x->arr5[j];
            n++;
         }
         overlap[4] = 1;
      }
      if (prob >= (y->score3[4]) && prob<(y->score3[5]) && overlap[5] == 0) {
         for (j = 0; j<10; j++) {
            z->choice[n] = x->arr6[j];
            n++;
         }
         overlap[5] = 1;
      }
      if (prob >= (y->score3[5]) && prob<(y->score3[6]) && overlap[6] == 0) {
         for (j = 0; j<10; j++) {
            z->choice[n] = x->arr7[j];
            n++;
         }
         overlap[6] = 1;
      }
      if (prob >= (y->score3[6]) && prob <= (y->score3[7]) && overlap[7] == 0) {
         for (j = 0; j<10; j++) {
            z->choice[n] = x->arr8[j];
            n++;
         }
         overlap[7] = 1;
      }
      for (j = 0; j<8; j++) {
         if (overlap[i] == 1) {
            count++;
         }
      }
   }
   j = 0;
   for (i = 0; i<40; i++) { // 편의를 위해 40짜리 배열에 받아논 값들을 10짜리 4개의 배열로 나눠준다
      if (i >= 0 && i<10) {
         z->choice1[j] = z->choice[i];
         j++;
      }
      if (i >= 10 && i<20) {
         z->choice2[j] = z->choice[i];
         j++;
      }
      if (i >= 20 && i<30) {
         z->choice3[j] = z->choice[i];
         j++;
      }
      if (i >= 30 && i<40) {
         z->choice4[j] = z->choice[i];
         j++;
      }
      if (i == 10 || i == 20 || i == 30) {
         j = 0;
      }
   }
}

int cross_array(struct choice *x, struct cross *y) { // 규칙3 교차
   int i = 0;
   float prob = 0;

   for (i = 0; i<10; i++) {
      y->cross1[i] = 0;
      y->cross2[i] = 0;
      y->cross3[i] = 0;
      y->cross4[i] = 0;
      y->cross5[i] = 0;
      y->cross6[i] = 0;
      y->cross7[i] = 0;
      y->cross8[i] = 0;
   }
   // cross 구조체를 초기화해준다.


   //   cross1   //
   for (i = 0; i<10; i++) {
      prob = random();   // prob=0~1의 값을 갖게되는 변수
      if (prob<0.5) {          // 50%확률로 나눠주기 위함
         y->cross1[i] = x->choice1[i];   // 50%확률로 choice1배열에서 선택
      }
      else {
         y->cross1[i] = x->choice2[i];   // 나머지 50%확률로 choice2배열에서 선택
      }               // 위의 방식으로 8개의 배열을 선택해준다.
   }
   //   cross2   //
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob<0.5) {
         y->cross2[i] = x->choice2[i];
      }
      else {
         y->cross2[i] = x->choice3[i];
      }
   }
   //   cross3   //
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob<0.5) {
         y->cross3[i] = x->choice3[i];
      }
      else {
         y->cross3[i] = x->choice4[i];
      }
   }
   //   cross4   //
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob<0.5) {
         y->cross4[i] = x->choice4[i];
      }
      else {
         y->cross4[i] = x->choice1[i];
      }
   }
   //   cross5   //
   for (i = 0; i<10; i++) {
      prob = random();   // prob 0~1
      if (prob<0.5) {
         y->cross5[i] = x->choice1[i];
      }
      else {
         y->cross5[i] = x->choice2[i];
      }
   }
   //   cross6   //
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob<0.5) {
         y->cross6[i] = x->choice2[i];
      }
      else {
         y->cross6[i] = x->choice3[i];
      }
   }
   //   cross7   //
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob<0.5) {
         y->cross7[i] = x->choice3[i];
      }
      else {
         y->cross7[i] = x->choice4[i];
      }
   }
   //   cross8   //
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob<0.5) {
         y->cross8[i] = x->choice4[i];
      }
      else {
         y->cross8[i] = x->choice1[i];
      }
   }
}

int transition_array(struct cross *x) { // 규칙4 변이
   int i = 0;
   float prob = 0;

   for (i = 0; i<10; i++) {
      prob = random();
      if (prob <= 0.05) {         // 5%의 확률로 새로운 값을 넣어준다
         x->cross1[i] = ((int)RAND()) % 100 + 1; // 위의 배열 생성시 값을 넣어준 방법으로
      }                 // 1~100까지의 값을 random으로 넣어준다
   }
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob <= 0.05) {
         x->cross2[i] = ((int)RAND()) % 100 + 1;
      }
   }
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob <= 0.05) {
         x->cross3[i] = ((int)RAND()) % 100 + 1;
      }
   }
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob <= 0.05) {
         x->cross4[i] = ((int)RAND()) % 100 + 1;
      }
   }
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob <= 0.05) {
         x->cross5[i] = ((int)RAND()) % 100 + 1;
      }
   }
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob <= 0.05) {
         x->cross6[i] = (int)(RAND()) % 100 + 1;
      }
   }
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob <= 0.05) {
         x->cross7[i] = (int)(RAND()) % 100 + 1;
      }
   }
   for (i = 0; i<10; i++) {
      prob = random();
      if (prob <= 0.05) {
         x->cross8[i] = (int)(RAND()) % 100 + 1;
      }
   }

}

void recursion(struct arr *x, struct score *y) { // 교차 변이 카피 평가 반복
   int i = 0, j = 0;

   while (1) {            // if(y->score[i]>=7 안에 들어가 배열에 저장하고
      cross_array(&choice, &cross);        // return을 만날때까지 돌아가게 한다
      transition_array(&cross);
      copy_array(&arr, &cross);
      evaluate_array(&arr, &score);

      /*
      지금 arr1~arr8까지의 배열 중 어느 배열이 7점을 넘은 배열인지 확인할 수가 없다.
      score배열을 이용한다.
      score[0]에는 arr1배열의 점수가, score[1]에는 arr2 배열의 점수가 입력되어 있다.
      그러므로, if문으로 score[i]의 점수가 7을 넘는다면,
      i의 값을 이용하여 구분을 지어준다. i==0에 7점을 넘는다면
      arr1배열이, i==1에 7점을 넘는다면 arr2배열이다.
      나중에 출력할때를 위해 arr배열이란 곳에 저장을 해준다.
      */

      for (i = 0; i<8; i++) {
         if (y->score[i] >= 7) {
            if (i == 0) {
               for (j = 0; j<10; j++) {
                  x->arr[j] = x->arr1[j];
               }
            }
            if (i == 1) {
               for (j = 0; j<10; j++) {
                  x->arr[j] = x->arr2[j];
               }
            }
            if (i == 2) {
               for (j = 0; j<10; j++) {
                  x->arr[j] = x->arr3[j];
               }
            }
            if (i == 3) {
               for (j = 0; j<10; j++) {
                  x->arr[j] = x->arr4[j];
               }
            }
            if (i == 4) {
               for (j = 0; j<10; j++) {
                  x->arr[j] = x->arr5[j];
               }
            }
            if (i == 5) {
               for (j = 0; j<10; j++) {
                  x->arr[j] = x->arr6[j];
               }
            }
            if (i == 6) {
               for (j = 0; j<10; j++) {
                  x->arr[j] = x->arr7[j];
               }
            }
            if (i == 7) {
               for (j = 0; j<10; j++) {
                  x->arr[j] = x->arr8[j];
               }
            }
            return;
         }
      }
   }
}

void copy_array(struct arr *x, struct cross *y) { // 마지막으로 cross배열에 저장을 했던 것을
   int i = 0;               // arr배열로 옮겨준다.

   for (i = 0; i<10; i++) {
      x->arr1[i] = y->cross1[i];
      x->arr2[i] = y->cross2[i];
      x->arr3[i] = y->cross3[i];
      x->arr4[i] = y->cross4[i];
      x->arr5[i] = y->cross5[i];
      x->arr6[i] = y->cross6[i];
      x->arr7[i] = y->cross7[i];
      x->arr8[i] = y->cross8[i];
   }
}

void print_array(struct arr *x) {   // 최종 선택된 배열을 출력해준다.
   int i = 0;

   printf("final array=");
   for (i = 0; i<10; i++) {
      printf(" %d", x->arr[i]);
   }
   printf("\n");
}