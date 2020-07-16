#include<stdio.h>
#pragma warning (disable:4996)
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
int main() {
	FILE *input, *output;

	input = fopen("srtf.inp", "rt");
	output = fopen("srtf.out", "wt");

	int n;
	int a, b, c;
	fscanf(input, "%d", &n);
	vector<vector<int> > arr(n);
	vector<int> b_time(n);
	for (int i = 0; i < n; i++) {
		fscanf(input, "%d %d %d", &b, &a, &c);
		arr[i].push_back(a);
		arr[i].push_back(b);
		arr[i].push_back(c);
		arr[i].push_back(0);
	}

	sort(arr.begin(), arr.end());//���Ǽ� ����

	for (int i = 0; i < n; i++) {
		b_time[i] = arr[i][2];
	}

	int t_time[51] = { 0 };//turnaround time
	int now_time = arr[0][0];
	int next_time = arr[0][0];
	arr[0][3] = 1;//next_time check��
	int wait_time = 0;
	int min_index = 0;
	int check = 0;
	
	//int i = 0;
	while (1) {//����
		/*int x;
		for (x = 0; x < n; x++) {//��밡�ɽð�
			if (arr[x][3] == 0 && next_time != arr[x][0]) {
				next_time = arr[x][0];
				break;
			}
		}
		if (x < n) {//��밡�� �ð��� ������ ���� ��
			if (next_time - now_time < arr[i][2]) {//cpu����ð��� �� Ŭ��
				arr[i][2] -= (next_time - now_time);
				now_time = next_time;
			}
			else {
				now_time = arr[][2];

			}
		}
		for (int y = 0; y < n; y++) {//�� ���� �ƹ��ų�
			if (arr[i][2] != 0 && now_time >= arr[y][0]) {
				min_index = y;
				break;
			}
		}
		//now_time = arr[i][2] - next_time;
		*/
		if (now_time == next_time) {
			for (int x = 0; x < n; x++) {//��밡�ɽð�//next������ else
				if (arr[x][3] == 0 && next_time < arr[x][0]) {
					next_time = arr[x][0];
					arr[x][3] = 1;
					break;
				}
				if (x == n - 1) next_time = 0;
			}
		}
		if (next_time != 0) {
			if (next_time - now_time < arr[min_index][2]) {//cpu����ð��� �� Ŭ��
				arr[min_index][2] -= (next_time - now_time);
				now_time = next_time;
			}
			else {
				now_time += arr[min_index][2];
				arr[min_index][2] = 0;
				t_time[min_index] = now_time - arr[min_index][0];
			}
			
		}
		else {
			now_time += arr[min_index][2];
			arr[min_index][2] = 0;
			t_time[min_index] = now_time - arr[min_index][0];
		}
		
		//min_index
		for (int i = 0; i < n; i++) {
			if (arr[min_index][2] == 0) {
				for (int j = 0; j < n; j++) {
					if (arr[j][2] != 0) {
						min_index = j;
						break;
					}
				}
			}
			if (now_time >= arr[i][0] && arr[i][2] != 0) {
				if (arr[min_index][2] == arr[i][2]) {
					if (min_index > i) {
						min_index = i;
						//break;
					}
				}
				else if (arr[min_index][2] > arr[i][2]) {
					min_index = i;
					//break;
				}
			}
		}
		if (next_time != 0) {
			if (now_time < arr[min_index][0]) {
				now_time += (arr[min_index][0] - now_time);
			}
		}
		for (int i = 0; i < n; i++) {
			if (t_time[i] == 0) break;
			if (i == n - 1) check = 1;
		}
		if (check == 1) break;
	}
	for (int i = 0; i < n; i++) {
		wait_time += (t_time[i] - b_time[i]);
	}
	fprintf(output,"%d", wait_time);
	/*while (count < n - 1) {
		for (int i = 1; i < n; i++) {
			if (arr[i][3] == 0) {
				min_index = i;
				break;
			}
		}
		for (int i = 0; i < n; i++) {//now_time���� �۰ų� ������ �� cpu����ð� ���� ������
			if (arr[i][3] == 0 && now_time >= arr[i][0]) {
				if (arr[min_index][2] > arr[i][2]) {
					min_index = i;
				}
			}
		}
		arr[min_index][3] = 1;
		if (now_time < arr[min_index][0]) {//���
			now_time += (arr[min_index][0] - now_time);
		}
		wait_time += (now_time - arr[min_index][0]);
		if (min_index != n) {
			now_time += arr[min_index][2];
		}
		count++;
	}

	fprintf(output, "%d", wait_time);*/

	fclose(input);
	fclose(output);
}