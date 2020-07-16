#include<stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
vector<int>ttime;
vector<int>track;
vector<int>same(200);
vector<int>check;
int s;
int now_time = 0;
int now_track = 0;
void fcfs();
void sstf();
int main() {
	FILE *input, *output;
	input = fopen("disk.inp", "rt");
	output = fopen("disk.out", "wt");

	int a, b;
	char what, t;
	fscanf(input, "%c", &what);
	fscanf(input, "%c", &t);
	fscanf(input, "%c", &t); 
	fscanf(input, "%c", &t);
	fscanf(input, "%d", &s);
	while (1) {
		fscanf(input, "%d %d", &a, &b);
		if (a == -1 && b == -1)break;
		ttime.push_back(a);
		track.push_back(b);
		check.push_back(0);
		same[b]++;
	}
	if (what == 'F') fcfs();
	else sstf();

	fprintf(output, "%d %d", now_time, now_track);

	fclose(input);
	fclose(output);
}
void fcfs() {
	for (int i = 0; i < ttime.size();i++) {
		if (ttime[i] <= now_time) {
			now_time += s;
			now_time += (abs(now_track - track[i]));
			now_track = track[i];
		}
		else {
			now_time = ttime[i];
			now_time += s;
			now_time += (abs(now_track - track[i]));
			now_track = track[i];
		}
	}
}
void sstf() {
	int index, min;
	for (int i=0;i<track.size();) {//전체 i는 전체 다 썼는지 확인
		min = 0;
		for (int x = 0; x < track.size(); x++) {//가장 가까운거
			if (check[x] == 0 && now_time >= ttime[x]) {
				if (min == 0) {
					min = abs(track[x] - now_track);
					index = x;
				}
				else {
					if (min > abs(track[x] - now_track)) {
						min = abs(track[x] - now_track);
						index = x;
					}
				}
			}
			if (now_time < ttime[x]) {
				if (min == 0) {
					now_time = ttime[x];
					index = x;
				}
				break;
			}
		}
		/*
		now_time += s;
		now_time += ((abs(now_track - track[index]))*same[track[index]]);
		now_track = track[index];
		i += same[track[index]];*/
		int num = 0;
		if (same[track[index]] > 1) {
			for (int y = 0; y < check.size(); y++) {
				if (now_time >= ttime[y] && track[y] == track[index]) {
					if (check[y] == 0) {
						num++;
						check[y] = 1;
					}
				}
			}
		}
		else {
			num = 1;
			check[index] = 1;
		}
		now_time += s*num;
		now_time += (abs(now_track - track[index]));
		now_track = track[index];
		i += num;
	}
	
}