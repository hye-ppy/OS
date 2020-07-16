#include<stdio.h>
#pragma warning (disable:4996)
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
int main() {
	FILE *input, *output;

	input = fopen("fcfs.inp", "rt");
	output = fopen("fcfs.out", "wt");

	int n;
	int a, b, c;
	fscanf(input, "%d", &n);
	vector<vector<int> > arr(n);
	for (int i = 0; i < n; i++) {
		fscanf(input, "%d %d %d", &b, &a, &c);
		arr[i].push_back(a);
		arr[i].push_back(b);
		arr[i].push_back(c);
	}

	sort(arr.begin(), arr.end());//조건순 정렬
	
	int now_time = arr[0][2];
	int wait_time = 0;
	for (int i = 1; i < n; i++) {
		if (now_time < arr[i][0]) {//대기
			now_time += (arr[i][0] - now_time);
		}
		wait_time += (now_time - arr[i][0]);
		if (i != (n - 1)) {
			now_time += arr[i][2];
		}
	}

	fprintf(output, "%d", wait_time);

	fclose(input);
	fclose(output);
}