#include <iostream>
#include <algorithm>
#include<cstring>
#include <cmath>
#include <limits.h>
using namespace std;

int N;
int A[21][21] = { 0 }; //������ �� ������ �α�
int visit[21][21] = { 0 };//���ű� ��ȣ �Է�
int gapp = INT_MAX; //���ű��� �α� ������ �ּڰ� ��¿�

void getgap() {
    //4. ���ű� �� �α����� ���ϱ�
    int jh[6] = { 0 };//������ jh: �� ���ű��� �α� ����
    int minn = INT_MAX; //Ʋ�� ������ �� �ڵ�
    int maxx = INT_MIN; // 0<A[r][c]<101
    //�ڷ����� �ִ�/�ּڰ�
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            jh[visit[i][j]] += A[i][j];
        }
        //����pr: ū ���� ���� �� ������ switch ���� ���� if���� ���� �������� �˾ƺ���
    }
    for (int i = 1; i <= 5; i++) {
        if (minn > jh[i]) {
            minn = jh[i];
        }
        if (maxx < jh[i]) {
            maxx = jh[i];
        }
    }
    if (gapp > maxx - minn) {
        gapp = maxx - minn;
        //for (int i = 1; i <= 5; i++) { cout << jh[i]; }
    }
}
void grid(int x, int y, int d1, int d2) {
    memset(visit, 0, sizeof(visit));

    //1. ��輱 5�� ���ű��� ����
    for (int i = 0; i <= d1; i++) {
        visit[x + i][y - i] = 5;
        visit[x + d2 + i][y + d2 - i] = 5;
    }
    for (int i = 0; i <= d2; i++) {
        visit[x + i][y + i] = 5;
        visit[x + d1 + i][y - d1 + i] = 5;
    }

    //2. ��輱 ���� 5�� ���ű��� ����
    for (int i = x + 1; i < x + d1 + d2; i++) {
        bool switchh = false;
        //switchh�� �� ����
        for (int j = 1; j <= N; j++) {
            if (visit[i][j] == 5) {
                //��輱�� ������ switchh�� �� �ٲٱ�
                switchh = switchh ? false : true;
            }
            if (switchh) {
                //switchh�� true�϶� ��輱 �������� ���Դٰ� �����ϰ�
                //5�� ���ű��� ����
                visit[i][j] = 5;
            }
        }
    }
    //3. ������ ���ű� ��ȣ �Է�
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if(visit[i][j] == 5) { continue; }
            if (i >= 1 && i < x + d1 && 1 <= j && j <= y) {
                visit[i][j] = 1;
            }
            else if (i >= 1 && i <= x + d2 && y < j && j <= N) {
                visit[i][j] = 2;
            }
            else if (x + d1 <= i && i <= N && 1 <= j && j < y - d1 + d2) {
                visit[i][j] = 3;
            }
            else if (x + d2 < i && i <= N && y - d1 + d2 <= j && j <= N) {
                visit[i][j] = 4;
            }
        }
    }
    //4. ���ű� �� �α����� ���ϱ�
    getgap();
}
int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> A[i][j];
        }
    }
    //0. x, y, d1, d2�� �θ�Ʈ ������ �� ����
    for (int a = 1; a <= N - 2; a++) {
        for (int b = 2; b <= N - 1; b++) {
            for (int c = 1; a + c <= N - 2 && b - c >= 1; c++) {
                for (int d = 1; a + c + d <= N && b + d <= N; d++) {
                    grid(a, b, c, d);
                }
            }
        }
    }

    //5. �� ���
    cout << gapp;
}