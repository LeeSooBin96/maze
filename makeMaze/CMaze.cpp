#include "CMaze.h"

/* ������ */
/* parameter : �̷� ũ�� */
CMaze::CMaze(int size)
{
	m_nSize = size;
	m_pMaze = new char[m_nSize*m_nSize]; //�� ����
	//�� �ʱ�ȭ
	initializeMaze(m_pMaze,1); //1�� �ʱ�ȭ
	m_pMaze[0] = 3; m_pMaze[(m_nSize - 1) * (m_nSize + 1)] = 4;//�����, ������ ����
}
/* �ı��� */
CMaze::~CMaze()
{
	delete[] m_pMaze;
}
/* �̷� �� �ʱ�ȭ */
/* parameter : �� ������, �ʱ�ȭ �� */
/* return : void */
void CMaze::initializeMaze(char* maze,char c)
{
	for (int j = 0; j < m_nSize; ++j) {
		for (int i = 0; i < m_nSize; ++i) {
			maze[j * m_nSize + i] = c;
		}
	}
}
/* �̷� �� ���� */
/* parameter : void */
/* return : �� ���� ���� */
bool CMaze::makeMaze()
{
	/* ������ */
	location* start = { NULL };
	start = createLocation(0, 0, NULL); //������ ����
	if (start == NULL) {
		cout << "������ ���� ����! \n";
		exit(1);
	}
	srand(time(NULL));
	
	for(int i=0;i<10;++i)
	buildRoad(&start); //�� �����

	bufferPrint(m_pMaze); //�� ���
	return false;
}
/* �� ����� */
/* parameter : Ž�� ���� */
/* return : �游��� ���� ���� bool */
bool CMaze::buildRoad(location** a)
{
	int nRow = (*a)->row;
	int nCol = (*a)->col;
	int nDir = rand() % 4; //���� ���� ����
	switch (nDir)
	{
	case 0: //��
		if (nRow > 0 && m_pMaze[nCol * m_nSize + nRow - 1] == 1) { //���� ���� �ƴϰ� �������� ���϶�
			if (nRow == 1 || m_pMaze[nCol * m_nSize+nRow-2]!=1) { //�� �ǳ����� ��(1)�� �ƴҶ�
				/* �������� �ձ� */
				if (rand() % 2 == 0) { //50%Ȯ����
					m_pMaze[nCol * m_nSize + nRow - 1] = 0;
					*a = createLocation(nRow - 1, nCol, *a);
					return true;
				}
			}
			else { //�� �ǳ����� ���̸� �������� ���� ����
				m_pMaze[nCol * m_nSize + nRow - 1] = 0;
				*a = createLocation(nRow - 1, nCol, *a);
				return true;
			}
		}
		break;
	case 1: //��
		if (nCol < m_nSize-1 && m_pMaze[(nCol+1) * m_nSize + nRow] == 1) { //���� ���� �ƴϰ� �������� ���϶�
			if (nCol == m_nSize-2 || m_pMaze[(nCol + 2) * m_nSize + nRow] != 1) { //�� �ǳ����� ��(1)�� �ƴҶ�
				/* �������� �ձ� */
				if (rand() % 2 == 0) { //50%Ȯ����
					m_pMaze[(nCol + 1) * m_nSize + nRow] = 0;
					*a = createLocation(nRow, nCol+1, *a);
					return true;
				}
			}
			else { //�� �ǳ����� ���̸� �������� ���� ����
				m_pMaze[(nCol + 1) * m_nSize + nRow] = 0;
				*a = createLocation(nRow, nCol + 1, *a);
				return true;
			}
		}
		break;
	case 2: //��
		if (nRow < m_nSize-1 && m_pMaze[nCol * m_nSize + nRow + 1] == 1) { //���� ���� �ƴϰ� �������� ���϶�
			if (nRow == m_nSize - 2 || m_pMaze[nCol * m_nSize + nRow + 2] != 1) { //�� �ǳ����� ��(1)�� �ƴҶ�
				/* �������� �ձ� */
				if (rand() % 2 == 0) { //50%Ȯ����
					m_pMaze[nCol * m_nSize + nRow + 1] = 0;
					*a = createLocation(nRow+1, nCol, *a);
					return true;
				}
			}
			else { //�� �ǳ����� ���̸� �������� ���� ����
				m_pMaze[nCol * m_nSize + nRow + 1] = 0;
				*a = createLocation(nRow + 1, nCol, *a);
				return true;
			}
		}
		break;
	case 3: //��
		if (nCol > 0 && m_pMaze[(nCol - 1) * m_nSize + nRow] == 1) { //���� ���� �ƴϰ� �������� ���϶�
			if (nCol == 1 || m_pMaze[(nCol - 2) * m_nSize + nRow] != 1) { //�� �ǳ����� ��(1)�� �ƴҶ�
				/* �������� �ձ� */
				if (rand() % 2 == 0) { //50%Ȯ����
					m_pMaze[(nCol - 1) * m_nSize + nRow] = 0;
					*a = createLocation(nRow, nCol-1, *a);
					return true;
				}
			}
			else { //�� �ǳ����� ���̸� �������� ���� ����
				m_pMaze[(nCol - 1) * m_nSize + nRow] = 0;
				*a = createLocation(nRow, nCol - 1, *a);
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}
/* �ű� location 1�� ���� */
/* parameter : row, col ��ǥ��, ���� ��ǥ */
/* return : �ű� ������ ����ü �ּ� */
location* CMaze::createLocation(int row, int col, location* a)
{
	location* temp = new location;
	if (temp == NULL)
		return NULL;
	temp->row = row;
	temp->col = col;
	temp->pre = a;
	return temp;
}
/* �ű� find 1�� ���� */
/* parameter : location* a */
/* return : �ű� ������ ����ü �ּ� */
findPoint* CMaze::createFind(location* a)
{
	findPoint* temp = new findPoint;
	if (temp == NULL)
		return NULL;
	temp->loc = a;
	temp->next = NULL;
	return temp;
}
/* find ���Ḯ��Ʈ�� ���� ���� ��(head) ���� */
/* parameter : find ���� �� head�� �ּ� */
/* return : void */
void CMaze::removeFind(findPoint** head)
{
	findPoint* temp = (*head)->next;
	delete (*head);
	*head = temp;
}
/* ���۷� �޾Ƽ� ��� */
/* parameter : �� ������ */
/* retrun : void */
void CMaze::bufferPrint(char* maze)
{
	static char* pFrontBuffer = new char[m_nSize * m_nSize];
	initializeMaze(pFrontBuffer, ' ');

	/* ���� �̷ο� front_buffer(���� �̷�)�� �ִ� �̷� �� */
	for (int i = 0; i < m_nSize; ++i)
		for (int j = 0, j2 = 0; j < m_nSize; ++j)
		{
			if (pFrontBuffer[j*m_nSize+i] != maze[j * m_nSize + i])
			{
				mazePrint(i, j2, maze[j*m_nSize+i]);
				// �ٲ� �κ� ȭ�鿡 ���
				pFrontBuffer[j * m_nSize + i] = maze[j * m_nSize + i];
				// �ٲ� �κ��� ��� �� front_buffer�� ����
			}
			j2 += 2; 
		}
}
/* �ѱ��� ��� */
/* prarameter : ��ǥ �� x�� y, �ٲ� ���� */
/* return : void */
void CMaze::mazePrint(int x, int y, char c)
{
	gotoxy(10 + y, 5 + x);	// ��� ����� ���� ����� ������
	switch (c)
	{
	case 0: //��
		cout << "��";
		//printf("��");
		break;
	case 1: //��
		cout << "��";
		//printf("��");
		break;
	case 2: //��������
		cout << "��";
		//printf("��");
		break;
	case 3: //�����
		cout << "��";
		//printf("��");
		break;
	case 4: //������
		cout << "��";
		//printf("��");
		break;
	case 5: //���� ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "��";
		//printf("��");
		break;
	}
	gotoxy(10 + m_nSize, 5 + m_nSize); // ��� �� Ŀ�� ��� ��ġ
}
/* �ܼ� ��� ��ǥ ���� */
/* parameter : x��, y�� */
/* return : void */
void CMaze::gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}