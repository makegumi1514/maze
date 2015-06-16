#include <iostream>
using namespace std;

void createMaze(int x, int y, int **maze, int type);

int main(){
	bool error = false;
	int x, y, type;
	while (!error){
		cout << "x:";
		cin >> x;
		cout << "y:";
		cin >> y;
		cout << "type:";
		cin >> type;
		cout << endl;
		if (x % 2 == 0 || y % 2 == 0) cout << "error" << endl;
		else error = true;
	}

	int** maze = new int*[y];		//2�����z��̓��I�m��
	for (int i = 0; i < y; i++){
		maze[i] = new int[x];
	}

	createMaze(x, y, maze, type);

	for (int i = 0; i < y; i++){
		for (int j = 0; j < x; j++){
			//cout << maze[i][j];
			if (maze[i][j] == 1) cout << "#";
			else cout << " ";
			if (j == x - 1) cout << endl;
		}
	}

	for (int i = 0; i < y; i++){
		delete[] maze[i];
	}
	delete[] maze;
	return 0;
}

void createMaze(int x, int y, int **maze, int type){
	bool stop = true;
	bool farst = true;
	bool end = false;
	int curentX, curentY, random, stopCount;
	curentX = curentY = random = stopCount = 0;
	switch (type){
	case 0:
		/*�_�|���@*/
		//���H�̏�����
		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				if (i == 0 || i == (y - 1)){
					maze[i][j] = 1;
				}
				else if (j == 0 || j == (x - 1)){
					maze[i][j] = 1;
				}
				else if (i % 2 == 0 && j % 2 == 0){
					maze[i][j] = 1;
				}
				else{
					maze[i][j] = 0;
				}
			}
		}
		//���H�̍쐬
		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				random = rand();
				if (j != 0 && j != x - 1 && j % 2 == 0){
					//�ŏ��̈�s�͏㉺���E�����_���ɖ_��|��
					if (i == 2){
						if (random % 4 == 0) maze[i - 1][j] = 1;		//��ɓ|��
						if (random % 4 == 1) maze[i + 1][j] = 1;		//���ɓ|��
						if (random % 4 == 2) maze[i][j + 1] = 1;		//�E�ɓ|��
						if (random % 4 == 3) maze[i][j - 1] = 1;		//���ɓ|��
					}
					//�ȍ~�̍s�͏�ɂ͓|���Ȃ�
					else if (i > 3 && i <= y - 3 && i % 2 == 0){
						if (maze[i][j -1] != 1){
							if (random % 2 == 0) maze[i + 1][j] = 1;
							if (random % 2 == 1) maze[i][j - 1] = 1;
						}
						else if (maze[i][j + 1] != 1){
							if (random % 2 == 0) maze[i + 1][j] = 1;
							if (random % 2 == 1) maze[i][j + 1] = 1;
						}
					}
				}
			}
		}
		break;
	case 1:
		/*���@��@(���̂΂��@)*/
		//���H�̏�����
		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				//���H�̊O�ɓ����̂΂��̂�h�����߂ɂ��炩���ߊO���𓹂ɂ���
				if (i == 0 || i == y - 1 || j == 0 || j == x - 1) maze[i][j] = 0;
				else maze[i][j] = 1;
			}
		}
		//���H�̍쐬
		while (!end){
			if (farst){
				curentY = rand() % y;
				curentX = rand() % x;
				maze[curentY][curentX] = 0;
				farst = false;
			}
			else if (stop){
				for (int i = 0; i < y; i++){
					for (int j = 0; j < x; j++){
						if (maze[i][j] == 0){
							stop = false;
							curentY = i;
							curentX = j;
						}
					}
				}
			}
			else{
				random = rand();
				if (random % 4 == 0 && maze[curentY - 2][curentX] != 0){
					maze[curentY - 2][curentX] = maze[curentY - 1][curentX] = 0;
					curentY -= 2;
				}
				else if (random % 4 == 1 && maze[curentY + 2][curentX] != 0){
					maze[curentY + 2][curentX] = maze[curentY + 1][curentX] = 0;
					curentY += 2;
				}
				else if (random % 4 == 2 && maze[curentY][curentX - 2] != 0){
					maze[curentY][curentX - 2] = maze[curentY][curentX - 1] = 0;
					curentX -= 2;
				}
				else if (random % 4 == 3 && maze[curentY][curentX + 2] != 0){
					maze[curentY][curentX + 2] = maze[curentY][curentX + 1] = 0;
					curentX += 2;
				}
				else stop = true;
			}
		}
		break;
	case 2:
		/*�ǂ̂΂��@*/
		//���H�̏�����
		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				if ((i == 0 || i == y - 1) || (j == 0 || j == x - 1)){
					maze[i][j] = 1;
				}
			}
		}
		//���H�̍쐬
		while (stopCount < 1000){
			if (stop){
				random = rand();
				if (random % 4 == 0) curentY = 0, curentX = (rand() % (x / 2)) * 2;				//��̕ǂ���L�΂�
				else if (random % 4 == 1) curentY = y - 1, curentX = (rand() % (x / 2)) * 2;	//���̕�
				else if (random % 4 == 2) curentY = (rand() % (y / 2)) * 2, curentX = 0;		//���̕�
				else if (random % 4 == 3) curentY = (rand() % (y / 2)) * 2, curentX = x - 1;	//�E�̕�
				stop = false;
				stopCount++;
			}
			else{
				random = rand();
				if (random % 4 == 0 && curentY >= 2 && maze[curentY - 2][curentX] != 1){
					maze[curentY - 2][curentX] = maze[curentY - 1][curentX] = 1;
					curentY -= 2;
				}
				else if (random % 4 == 1 && curentY <= y - 3 && maze[curentY + 2][curentX] != 1){
					maze[curentY + 2][curentX] = maze[curentY + 1][curentX] = 1;
					curentY += 2;
				}
				else if (random % 4 == 2 && curentX >= 2 && maze[curentY][curentX - 2] != 1){
					maze[curentY][curentX - 2] = maze[curentY][curentX - 1] = 1;
					curentX -= 2;
				}
				else if (random % 4 == 3 && curentX <= x - 3 && maze[curentY][curentX + 2] != 1){
					maze[curentY][curentX + 2] = maze[curentY][curentX + 1] = 1;
					curentX += 2;
				}
				else stop = true;
			}
		}
		break;
	case 3:
		break;
	default:
		cout << "error" << endl;
		break;
	}
}