#include <iostream>
#include <time.h>
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

	int** maze = new int*[y];		//2次元配列の動的確保
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
	srand((unsigned)time(NULL));

	bool stop = true;
	bool stop_wall = false;
	bool farst = true;
	bool end = false;
	bool select = false;
	int currentX, currentY, random, stopCount;
	currentX = currentY = random = stopCount = 0;
	switch (type){
	case 0:
		/*棒倒し法*/
		//迷路の初期化
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
		//迷路の作成
		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				random = rand();
				if (j != 0 && j != x - 1 && j % 2 == 0){
					//最初の一行は上下左右ランダムに棒を倒す
					if (i == 2){
						if (random % 4 == 0) maze[i - 1][j] = 1;		//上に倒す
						if (random % 4 == 1) maze[i + 1][j] = 1;		//下に倒す
						if (random % 4 == 2) maze[i][j + 1] = 1;		//右に倒す
						if (random % 4 == 3) maze[i][j - 1] = 1;		//左に倒す
					}
					//以降の行は上には倒さない
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
		/*穴掘り法(道のばし法)*/
		//迷路の初期化
		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				//迷路の外に道をのばすのを防ぐためにあらかじめ外周を道にする
				if (i == 0 || i == y - 1 || j == 0 || j == x - 1) maze[i][j] = 0;
				else maze[i][j] = 1;
			}
		}
		//迷路の作成
		while (!end){
			if (farst){
				currentY = rand() % y;
				currentX = rand() % x;
				maze[currentY][currentX] = 0;
				farst = false;
			}
			else if (stop){
				for (int i = 0; i < y; i++){
					for (int j = 0; j < x; j++){
						if (maze[i][j] == 0){
							stop = false;
							currentY = i;
							currentX = j;
						}
					}
				}
			}
			else{
				random = rand();
				if (random % 4 == 0 && maze[currentY - 2][currentX] != 0){
					maze[currentY - 2][currentX] = maze[currentY - 1][currentX] = 0;
					currentY -= 2;
				}
				else if (random % 4 == 1 && maze[currentY + 2][currentX] != 0){
					maze[currentY + 2][currentX] = maze[currentY + 1][currentX] = 0;
					currentY += 2;
				}
				else if (random % 4 == 2 && maze[currentY][currentX - 2] != 0){
					maze[currentY][currentX - 2] = maze[currentY][currentX - 1] = 0;
					currentX -= 2;
				}
				else if (random % 4 == 3 && maze[currentY][currentX + 2] != 0){
					maze[currentY][currentX + 2] = maze[currentY][currentX + 1] = 0;
					currentX += 2;
				}
				else stop = true;
			}
		}
		break;
	case 2:
		/*壁のばし法*/
		//迷路の初期化
		for (int i = 0; i < y; i++){
			for (int j = 0; j < x; j++){
				if ((i == 0 || i == y - 1) || (j == 0 || j == x - 1)){
					maze[i][j] = 1;
				}
			}
		}
		//迷路の作成
		//while (stopCount < 1000){
		//	if (stop){
		//		random = rand();
		//		if (random % 4 == 0) curentY = 0, curentX = (rand() % (x / 2)) * 2;				//上の壁から伸ばす
		//		else if (random % 4 == 1) curentY = y - 1, curentX = (rand() % (x / 2)) * 2;	//下の壁
		//		else if (random % 4 == 2) curentY = (rand() % (y / 2)) * 2, curentX = 0;		//左の壁
		//		else if (random % 4 == 3) curentY = (rand() % (y / 2)) * 2, curentX = x - 1;	//右の壁
		//		stop = false;
		//		stopCount++;
		//	}
		//	else{
		//		random = rand();
		//		if (random % 4 == 0 && curentY >= 2 && maze[curentY - 2][curentX] != 1){
		//			maze[curentY - 2][curentX] = maze[curentY - 1][curentX] = 1;
		//			curentY -= 2;
		//		}
		//		else if (random % 4 == 1 && curentY <= y - 3 && maze[curentY + 2][curentX] != 1){
		//			maze[curentY + 2][curentX] = maze[curentY + 1][curentX] = 1;
		//			curentY += 2;
		//		}
		//		else if (random % 4 == 2 && curentX >= 2 && maze[curentY][curentX - 2] != 1){
		//			maze[curentY][curentX - 2] = maze[curentY][curentX - 1] = 1;
		//			curentX -= 2;
		//		}
		//		else if (random % 4 == 3 && curentX <= x - 3 && maze[curentY][curentX + 2] != 1){
		//			maze[curentY][curentX + 2] = maze[curentY][curentX + 1] = 1;
		//			curentX += 2;
		//		}
		//		else stop = true;
		//	}
		//}
		while (stopCount < 10000){
			while (!select){
				int randomY = (rand() % ((y + 1) / 2)) * 2;
				int randomX = (rand() % ((x + 1) / 2)) * 2;
				if (maze[randomY][randomX] == 1){
					currentY = randomY;
					currentX = randomX;
					select = true;
					stop_wall = false;
				}
			}
			while (!stop_wall){
				if (rand() % 4 == 0 && currentY >= 2 && maze[currentY - 2][currentX] != 1){
					maze[currentY - 2][currentX] = maze[currentY - 1][currentX] = 1;
					currentY -= 2;
				}
				else if (rand() % 4 == 1 && currentY <= y - 3 && maze[currentY + 2][currentX] != 1){
					maze[currentY + 2][currentX] = maze[currentY + 1][currentX] = 1;
					currentY += 2;
				}
				else if (rand() % 4 == 2 && currentX >= 2 && maze[currentY][currentX - 2] != 1){
					maze[currentY][currentX - 2] = maze[currentY][currentX - 1] = 1;
					currentX -= 2;
				}
				else if (rand() % 4 == 3 && currentX <= x - 3 && maze[currentY][currentX + 2] != 1){
					maze[currentY][currentX + 2] = maze[currentY][currentX + 1] = 1;
					currentX += 2;
				}
				else{
					stop_wall = true;
					select = false;
					stopCount++;
				}
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