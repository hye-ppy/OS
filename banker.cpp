#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#pragma warning(disable:4996)
int m, n;
queue<int>q;
bool safe(vector<int> &av, vector<vector<int> > &need, vector<vector<int> > &alloc, vector<int> &req, vector<vector<int> > &max);
int main() {
	FILE *input, *output;
	input = fopen("banker.inp", "rt");
	output = fopen("banker.out", "wt");

	int a;
	fscanf(input, "%d %d", &n, &m);//n,m 
	char arr[7], t;//무슨 자원인지
	vector<vector<int> > req(1000);//request
	vector<int> rel(m + 1);//release
	vector<int> max_m;//최대자원
	vector<int> av(m);
	vector<vector<int> > max(n);
	vector<vector<int> > alloc(n);
	vector<vector<int> > need(n);
	for (int i = 0; i < m; i++) {//max_m
		fscanf(input, "%d", &a);
		max_m.push_back(a);
	}
	for (int i = 0; i < n; i++) {//max
		for (int j = 0; j < m; j++) {
			fscanf(input, "%d", &a);
			max[i].push_back(a);
		}
	}
	for (int i = 0; i < n; i++) {//alloc
		for (int j = 0; j < m; j++) {
			fscanf(input, "%d", &a);
			alloc[i].push_back(a);
		}
	}
	for (int i = 0; i < n; i++) {//need
		for (int j = 0; j < m; j++) {
			a = max[i][j] - alloc[i][j];
			need[i].push_back(a);
		}
	}
	for (int i = 0; i < n; i++) {//av
		for (int j = 0; j < m; j++) {
			av[j] += alloc[i][j];
		}
		if (i == n - 1) {
			for (int j = 0; j < m; j++) {
				av[j] = max_m[j] - av[j];
			}
		}
	}
/*	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d", need[i][j]);
		}
		printf("\n");
	}*/
	int x = 0;
	fscanf(input, "%c", &t);
	fscanf(input, "%c", &t);
	while (1) {
		fscanf(input, "%c", &t);
		for (int i = 0; i < 7; i++) {
			fscanf(input, "%c", &arr[i]);
		}
		//printf("%c", arr[2]);
		//fscanf(input, "%d", &p_num);
		if (arr[2] == 'i') break;//quit이면 끝
		if (arr[2] == 'q') {//request면 safe 확인하고 출력
			for (int i = 0; i < m+2; i++) {
				if (i == 0) {
					req[x].push_back(0);
				}
				else {
					fscanf(input, "%d", &a);
					req[x].push_back(a);
				}
			}
			/*for (int i = 0; i < m+2; i++) {
				printf("%d ", req[x][i]);
			}*/
			if (safe(av, need, alloc, req[x], max) == false) {
				q.push(x);
			}
			x++;
		}
		if (arr[2] == 'l') {
			for (int i = 0; i < m + 1; i++) {				
				fscanf(input, "%d", &rel[i]);
			}
			for (int i = 0; i < m; i++) {
				av[i] += rel[i+1];
				alloc[rel[0]][i] -= rel[i + 1];
				need[rel[0]][i] += rel[i + 1];
			}
			if (!q.empty()) {
				int qq;
				int size = q.size();
				for (int i = 0; i < size; i++) {
					qq = q.front();
					if (safe(av, need, alloc, req[qq], max) == false) {
						q.push(qq);
					}
					q.pop();
				}
			}
			/*for (int i = 0; i < m; i++) {
				printf("%d ", av[i]);
			}
			printf("\n");*/
		}
		
		for (int i = 0; i < m; i++) {
			fprintf(output, "%d ", av[i]);
		}
		fprintf(output, "\n");
		/*for (int i = 1; i < m; i++) {
			fscanf(input, "%d", &p_m[i]);
		}
		for (int i = 0; i < m; i++) {
			printf("%d ", p_m[i]);
		}
		printf("\n");*/
	}
	
	fclose(input);
	fclose(output);
}
bool safe(vector<int> &av, vector<vector<int> > &need, vector<vector<int> > &alloc, vector<int> &req, vector<vector<int> > &max) {
	vector<int> c_av(av);
	vector<int> c_req(req);
	vector<vector<int> > c_need(need);
	vector<vector<int> > c_alloc(alloc);
	vector<int> check(n);//safe체크용
	for (int i = 0; i < m; i++) {//safe 확인전 값 바꾸기
		if (c_av[i] - c_req[i + 2] < 0) return false;//할당안되면 끝
		else {
			c_av[i] -= c_req[i + 2];
		}
		if (c_need[req[1]][i] - c_req[i + 2] < 0) return false;//할당안되면 끝
		else {
			c_need[req[1]][i] -= c_req[i + 2];
		}
		if (c_alloc[req[1]][i] + c_req[i + 2] > max[req[1]][i]) return false;//할당안되면 끝
		else {
			c_alloc[req[1]][i] += c_req[i + 2];
		}
	}
	int turn = 0;//바뀐거 있나없나
	int count = 0;//check==m이면 safe만족
	for (int i = 0; i < n; i++) {
		if (check[i] == 0) {
			for (int j = 0; j < m; j++) {
				if (c_av[j] < c_need[i][j]) break;
				if (j == m - 1) {//need만족하면alloc+av
					for (int k = 0; k < m; k++) {
						c_av[k] += c_alloc[i][k];
					}
					check[i] = 1;
					turn = 1;
					count++;
				}
			}
		}
		if (i == n - 1) {
			if (count == n) {//값 바꿔주기
				for (int i = 0; i < m; i++) {
					av[i] -= req[i + 2];
					need[req[1]][i] -= req[i + 2];
					alloc[req[1]][i] += req[i + 2];
				}
				return true;
			}
			if (turn == 0) return false;
			else {
				turn = 0;
				i = -1;
			}
		}
	}
	
}

