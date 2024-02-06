#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

int W = 15;
int L = 15;
int show_w = 10, show_l = 12;

void remove_index(int[][2], int, int&);
void make_map(int[][4]);
void print_map(int[][4]);
void display(int[][4], int, int, int[2]);
int walk(char a, int[][4], int (&)[2]);
void start();
void finish();

int main()
{
    srand(time(NULL));
    start();

	int mapp[W * L][4];
	make_map(mapp);

	//print_map(mapp);
	int position[2] = { 0, 0 };
	display(mapp, show_w, show_l, position);

	char p;
    while(!(position[0] == W && position[1] == L - 1)){
        p = getch();
        if(walk(p, mapp, position)){
            display(mapp, show_w, show_l, position);
        }
    }
    finish();

	return 0;
}

void remove_index(int arr[][2], int index, int& arr_size)
{
	for (int i = index; i < arr_size; i++) {
		arr[i][0] = arr[i + 1][0];
		arr[i][1] = arr[i + 1][1];
	}
	arr_size--;
}

void make_map(int mapp[][4]) // fungsi untuk membuat map random
{
	int p1[] = { rand() % W, rand() % L };
	int saved[W * L][2];
	int opened_map[W][L];
	int saved_count = 1;

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < L; j++) {
			for (int k = 0; k < 4; k++) {
				mapp[i*L+j][k] = 0;
			}
			opened_map[i][j] = 0;
		}
	}
	mapp[W * L - 1][2] = 1;
	opened_map[p1[0]][p1[1]] = 1;
	saved[0][0] = p1[0];
	saved[0][1] = p1[1];

	while (saved_count > 0) {
		int is_open[4] = { 0 }, open = 0;
		int index = rand() % saved_count;
		int check[2] = { saved[index][0], saved[index][1] };
		int direction[2][4] = { {-1, 0, 1, 0},{0, 1, 0, -1} };

		for (int i = 0; i < 4; i++) {
			if (check[0] + direction[0][i] >= 0 && check[1] + direction[1][i] >= 0 && check[0] + direction[0][i] < W && check[1] + direction[1][i] < L && opened_map[check[0] + direction[0][i]][check[1] + direction[1][i]] == 0) {
				is_open[open] = i; open++;
			}
		}
		if (open) {
			int connect = rand() % open;
			opened_map[check[0] + direction[0][is_open[connect]]][check[1] + direction[1][is_open[connect]]] = 1;
			mapp[check[0]*L+check[1]][is_open[connect]] = 1;
			mapp[(check[0] + direction[0][is_open[connect]])*L+(check[1] + direction[1][is_open[connect]])][(is_open[connect] + 2) % 4] = 1;
			saved[saved_count][0] = check[0] + direction[0][is_open[connect]];
			saved[saved_count][1] = check[1] + direction[1][is_open[connect]];
			saved_count++;
		}
		else {
			remove_index(saved, index, saved_count);
		}
	}
}

void print_map(int mapp[][4]) // untuk memperlihatkan map yang terbentuk
{
    for (int i = 0; i < L * 4; i++) cout << '_';
	cout << "_\n";
	for (int i = 0; i < W; i++) {
		cout << '|';

		for (int j = 0; j < L; j++) {
			if (mapp[i*L+j][1]) cout << "    ";
			else cout << "   |";
		}
		cout << "\n|";
		for (int j = 0; j < L; j++) {
			if (mapp[i*L+j][2]) cout << "   ";
			else cout << "___";
			if (mapp[i*L+j][1]) cout << "_";
			else cout << '|';
		}
		cout << "\n";
	}
}

void display(int mapp[][4], int width, int length, int position[2]) // untuk menampilkan permainan
{
    system("cls");
	int showed[width][length][4];
	for (int w = position[0] - width / 2; w < position[0] + (width + 1) / 2; w++) {
		for (int l = position[1] - length / 2; l < position[1] + (length + 1) / 2; l++) {
			if (w < 0 || l < 0 || w >= W || l >= L) {
				for (int i = 0; i < 4; i++) {
					showed[w - position[0] + width / 2][l - position[1] + length / 2][i] = 2;
				}
			}
			else {
				for (int i = 0; i < 4; i++) {
					showed[w - position[0] + width / 2][l - position[1] + length / 2][i] = mapp[w*L+l][i];
				}
			}
		}
	}
	cout << "////";
	for (int i = 0; i < length; i++) cout << "////";
	cout << "\n";
	for (int i = 0; i < width; i++) {
        cout << "//";
		for (int j = 0; j < length; j++) {
            if (i == width / 2 && j == length / 2) cout << " @ ";
            else cout << "   ";
            if (j < length - 1 && showed[i][j][1] == 2 && showed[i][j + 1][3] == 0) cout << "|";
			else if (showed[i][j][1]) cout << " ";
			else cout << "|";
		}
		cout << "//\n//";
		for (int j = 0; j < length; j++) {
			if (i < width - 1 && showed[i][j][2] == 2 && showed[i + 1][j][0] == 0) {
                    cout << "____"; continue;
            }
			if (showed[i][j][2]) cout << "   ";
			else cout << "___";
			if (showed[i][j][1] == 1) cout << "_";
			else if (j < length - 1 && showed[i][j][1] == 2 && showed[i][j + 1][3] == 0) cout << '|';
			else if (showed[i][j][1] == 2) cout << ' ';
			else cout << '|';
		}
		cout << "//\n";
	}
    for (int i = 0; i < length; i++) cout << "////";
    cout << "////\n";
}

int walk(char a, int mapp[][4], int (&position)[2]) // fungsi untuk jalan, merubah posisi saat ditekan wasd
{
    switch(a){
    case 'w':
        if(mapp[position[0] * L + position[1]][0]){
            position[0]--;
            return 1;
        }
        cout<<"nabrak !\b\b\b\b\b\b\b\b"; return 0;
    case 'd':
        if(mapp[position[0]*L+position[1]][1]){
            position[1]++;
            return 1;
        }
        cout<<"nabrak !\b\b\b\b\b\b\b\b"; return 0;
    case 's':
        if(mapp[position[0]*L+position[1]][2]){
            position[0]++;
            return 1;
        }
        cout<<"nabrak !\b\b\b\b\b\b\b\b"; return 0;
    case 'a':
        if(mapp[position[0]*L+position[1]][3]){
            position[1]--;
            return 1;
        }
        cout<<"nabrak !\b\b\b\b\b\b\b\b"; return 0;
    default: cout << "apa itu?\b\b\b\b\b\b\b\b";
    }
    return 0;
}

void start() // yang ditampilkan saat mulai
{
    system("cls");
    char in;
    cout << "******* GAME GAJE *******\n\n"
    << "1: Pengaturan ukuran peta\n2: Pengaturan ukuran tampilan\nselain 1 dan 2: Mulai permainan\n\n";
    cin >> in;

    switch(in)
    {
        case '1':
            cout << "\nUkuran peta saat ini:\n" << W << " x " << L << "\n\n"
            << "Masukkan ukuran lebar dan panjang peta dipisah dengan spasi:\n";
            cin >> W >> L;
            start(); break;
        case '2':
            cout << "\nUkuran tampilan saat ini:\n" << show_w << " x " << show_l << "\n\n"
            << "Masukkan ukuran lebar dan panjang tampilan dipisah dengan spasi:\n";
            cin >> show_w >> show_l;
            start(); break;
        default: break;
    }
}

void finish() // yang ditampilkan saat selesai
{
    char c;
    cout
    <<"    _______   _   _    _   _    _____   _    _\n"
    <<"   |  _____| | | | \\  | | | |  / ____| | |  | |\n"
    <<"   | |       | | |  \\ | | | | | |      | |  | |\n"
    <<"   | |_____  | | |   \\| | | |  \\_\\__   | |__| |\n"
    <<"   |  _____| | | | |\\ \\ | | |     \\ \\  |  __  |\n"
    <<"   | |       | | | | \\  | | |  ____| | | |  | |\n"
    <<"   |_|       |_| |_|  \\_| |_| |_____/  |_|  |_|\n"
    <<"\nLagi?\n\n1 = ya\nselain 1 = tidak\n\n";
    cin >> c;

    if(c=='1'){
        system("cls");
        main();
    }
}
