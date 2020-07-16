#include<stdio.h>
#pragma warning (disable:4996)
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
int main() {
	FILE *input, *output;

	input = fopen("sjf.inp", "rt");
	output = fopen("sjf.out", "wt");

	int n;
	int a, b, c;
	fscanf(input, "%d", &n);
	vector<vector<int> > arr(n);
	for (int i = 0; i < n; i++) {
		fscanf(input, "%d %d %d", &b, &a, &c);
		arr[i].push_back(a);
		arr[i].push_back(b);
		arr[i].push_back(c);
		arr[i].push_back(0);
	}

	sort(arr.begin(), arr.end());//조건순 정렬

	int now_time = arr[0][2];
	arr[0][3] = 1;
	int wait_time = 0;
	int min_index;
	int count = 0;
	while (count < n-1) {
		for (int i = 1; i < n; i++) {
			if (arr[i][3] == 0) {
				min_index = i;
				break;
			}
		}
		for (int i = 0; i < n; i++) {//now_time보다 작거나 같은것 중 cpu실행시간 가장 작은것
			if (arr[i][3] == 0 && now_time >= arr[i][0]) {
				if (arr[min_index][2] > arr[i][2]) {
					min_index = i;
				}
			}
		}
		arr[min_index][3] = 1;
		if (now_time < arr[min_index][0]) {//대기
			now_time += (arr[min_index][0] - now_time);
		}
		wait_time += (now_time - arr[min_index][0]);
		if (min_index != n) {
			now_time += arr[min_index][2];
		}
		count++;
	}
	
	fprintf(output, "%d", wait_time);

	fclose(input);
	fclose(output);
}