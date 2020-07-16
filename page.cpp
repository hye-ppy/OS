#include<stdio.h>
#pragma warning(disable:4996)
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
queue<int>q;
queue<int>l_q;
vector<int>l_one;
vector<int>l_two;
vector<int>one;
vector<int>two;
vector<int>o_one;
vector<int>o_two;
vector<int>zero;
vector<int>pid;//opt
vector<int>pnum;//opt
vector<vector<int> >o_check(100);//opt
vector<vector<int> >l_check(100);
vector<vector<int> >check(100);
int k;
int l_cc = 1;
int cc = 1;
int lru_num = 0;
int fifo_num = 0;
int opt_num = 0;
void fifo(int x, int y);
void lru(int x, int y);
void opt();
int main() {
	FILE *input, *output;
	input = fopen("page.inp", "rt");
	output = fopen("page.out", "wt");
	//printf("%d", check.size());
	int a, b;
	fscanf(input, "%d", &k);
	while (1) {
		fscanf(input, "%d %d", &a, &b);
		pid.push_back(a);
		pnum.push_back(b);
		if (a == -1 && b == -1) break;
		fifo(a, b);
		lru(a, b);
	}
	opt();
	fprintf(output, "FIFO: %d\n", fifo_num);
	for (int i = 0; i < one.size(); i++) {
		fprintf(output, "%d %d %d\n",i , one[i], two[i]);
	}
	fprintf(output, "LRU: %d\n", lru_num);
	for (int i = 0; i < l_one.size(); i++) {
		fprintf(output, "%d %d %d\n",i , l_one[i], l_two[i]);
	}
	fprintf(output, "OPT: %d\n", opt_num-1);
	for (int i = 0; i < o_one.size(); i++) {
		fprintf(output, "%d %d %d\n",i , o_one[i], o_two[i]);
	}
	fclose(input);
	fclose(output);
}
void fifo(int x, int y) {
	int ch1 = 0;
	int temp, t;
	int count = 0;
	for (int i = 0; i < one.size(); i++) {//같은거 있는지 체크
		if (one[i] == x && two[i] == y) {
			return;
		}
	}
	fifo_num++;
	one.push_back(x);
	two.push_back(y);
	for (int i = 0; i < cc; i++) {
		if (check[i].size() == 0) {
			check[i].push_back(x);
			check[i].push_back(1);
			cc++;
			break;
		}
		if (check[i][0] == x) {
			if (check[i][1] < k) {//최대 프레임보다 적을때
				check[i][1]++;
			}
			else {//최대 프레임
				ch1 = 1;
			}
			break;
		}
	}
	if (ch1 == 1) {
		one.pop_back();
		two.pop_back();
		while (1) {//같은거 없을 때			
			temp = q.front();
			q.pop();
			//q.push(temp);
			count++;
			if (one[temp] == x) {
				two[temp] = y;
				int s = q.size();
				for (int i = 0; i < s - count + 1; i++) {
					t = q.front();
					q.pop();
					q.push(t);
				}
				q.push(temp);
				break;
			}
			q.push(temp);
		}
	}
	else {
		q.push(one.size() - 1);
	}
}
void lru(int x, int y) {
	int ch1 = 0;
	int temp, t;
	int count = 0;
	int ch = 0;
	for (int i = 0; i < l_one.size(); i++) {//같은거 있는지 체크
		if (l_one[i] == x && l_two[i] == y) {//여기 완성하면 됨
			while (1) {//같은거 없을 때			
				temp = l_q.front();
				l_q.pop();
				ch++;
				if (i == temp) {
					int s = l_q.size();
					for (int i = 0; i < s - ch + 1; i++) {
						t = l_q.front();
						l_q.pop();
						l_q.push(t);
					}
					l_q.push(temp);
					break;
				}
				l_q.push(temp);
			}
			return;
		}
	}
	lru_num++;
	l_one.push_back(x);
	l_two.push_back(y);
	for (int i = 0; i < l_cc; i++) {
		if (l_check[i].size() == 0) {
			l_check[i].push_back(x);
			l_check[i].push_back(1);
			l_cc++;
			break;
		}
		if (l_check[i][0] == x) {
			if (l_check[i][1] < k) {//최대 프레임보다 적을때
				l_check[i][1]++;
			}
			else {//최대 프레임
				ch1 = 1;
			}
			break;
		}
	}
	if (ch1 == 1) {
		l_one.pop_back();
		l_two.pop_back();
		while (1) {//같은거 없을 때			
			temp = l_q.front();
			l_q.pop();
			//q.push(temp);
			count++;
			if (l_one[temp] == x) {
				l_two[temp] = y;
				int s = l_q.size();
				for (int i = 0; i < s - count + 1; i++) {
					t = l_q.front();
					l_q.pop();
					l_q.push(t);
				}
				l_q.push(temp);
				break;
			}
			l_q.push(temp);
		}
	}
	else {
		l_q.push(l_one.size() - 1);
	}
}
void opt() {
	//int min = 0;
	int o_cc = 1;
	int ch1 = 0, ch, ch2 = 0;
	
	int index = 0;
	for (int x = 0; x < pid.size(); x++) {
		vector<int>n(k);
		vector<int>n1(k);
		ch = 0;
		ch2 = 0;
		ch1 = 0;
		for (int i = 0; i < o_one.size(); i++) {//같은거 있는지 체크
			if (o_one[i] == pid[x] && o_two[i] == pnum[x]) {
				ch = 1;
				//zero[i] = x;
				//zero.push_back(x);
				break;
			}
		}
		if (ch == 1) continue;
		opt_num++;
		o_one.push_back(pid[x]);
		o_two.push_back(pnum[x]);
		zero.push_back(x);
		for (int i = 0; i < o_cc; i++) {
			
			if (o_check[i].size() == 0) {
				o_check[i].push_back(pid[x]);
				o_check[i].push_back(1);
				o_cc++;
				break;
			}
			if (o_check[i][0] == pid[x]) {
				if (o_check[i][1] < k) {//최대 프레임보다 적을때
					o_check[i][1]++;
				}
				else {//최대 프레임
					ch1 = 1;
				}
				break;
			}
		}
		if (ch1 == 1) {
			o_one.pop_back();
			o_two.pop_back();
			zero.pop_back();
			index = 0;
			for (int i = 0; i < o_one.size(); i++) {//그 페이지가 k만큼 어디에 위치했는지
				if (pid[x] == o_one[i]) {//11 11 11
					n[index] = i;
					index++;
				}
				if (index == k) break;
			}
			for (int i = x + 1; i < pid.size(); i++) {//어느게 제일 늦게 쓰이는지 한개 + 없으면 zero작은거
				for (int y = 0; y < k; y++) {
					if (o_one[n[y]] == pid[i] && o_two[n[y]] == pnum[i]) {
						n1[y] = 1;
						for (int z = 0; z < k; z++) {
							if (n1[z] == 1) {
								ch2++;
							}
						}
						if (ch2 == k - 1) ch2 = 2;
						else ch2 = 0;
						break;
					}
				}
				if (ch2 == 2) {
					for (int z = 0; z < k; z++) {
						if (n1[z] == 0) {
							o_two[n[z]] = pnum[x];
							zero[n[z]] = x;
							break;
						}
					}
					break;
				}
				if (i == pid.size() - 1) {
					int ccc = 0;
					int min;
					int min_index;
					for (int y = 0; y < k; y++) {
						if (n1[y] == 0) {
							if (ccc == 0) {
								ccc = 1;
								min = zero[n[y]];
								min_index = n[y];
							}
							else {
								if (min > zero[n[y]]) {
									min = zero[n[y]];
									min_index = n[y];
								}
							}
						}
					}
					o_two[min_index] = pnum[x];
					zero[min_index] = x;
					break;
				}
			}
		}
		if (pid[x] == -1 && pnum[x] == -1) {
			o_one.pop_back();
			o_two.pop_back();
		}
	}
}