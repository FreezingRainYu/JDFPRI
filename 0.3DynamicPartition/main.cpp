#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>

using namespace std;

struct rd
{
	int flag;
	int size;
	string name;
	rd* next;
	rd(int f, int s, string nm = "", rd* n = nullptr) :flag(f), size(s), name(nm), next(n) {}
};

const int maxsize = 512; //����ڴ�
rd* freeq = new rd(0, maxsize); //�����������
rd* jobq; //��ռ�����棨���񣩶���

//���뺯��
int request(int sz, int stra)
{
	int reAddr; //���صĵ�ַ
	int sort = 0;
	rd* p = freeq;

	while (p != nullptr)
	{
		//����������С��������Ĵ�С
		if (p->size > (sz + 1))
		{
			p->size -= (sz + 1);
			reAddr = p->flag + p->size;
			sort = 1;
			break;
		}

		//����������С��������Ĵ�С
		else if (p->size == (sz + 1))
		{
			if (p == freeq)
			{
				freeq = freeq->next;
				reAddr = p->flag;
				break;
			}
			else
			{
				rd* f = freeq;
				while (f->next != p)
				{
					f = f->next;
				}
				f->next = p->next;
				reAddr = p->flag;
				break;
			}
		}

		else
		{
			p = p->next;
		}
	}

	//δ�ҵ����ʵ����������
	if (p == nullptr)
	{
		return -1;
	}
	
	//�״���Ӧ�㷨
	if (stra == 1)
	{
		return reAddr;
	}

	//�����Ӧ�㷨
	if (stra == 2)
	{
		if (sort == 1)
		{
			if (p != freeq)
			{
				rd* f = freeq;
				while (f->next != p)
				{
					f = f->next;
				}
				f->next = p->next;
				f = freeq;
				while (f != nullptr)
				{
					if (f->size > p->size)
					{
						p->next = freeq;
						freeq = p;
						break;
					}
					else if (f->size < p->size && f->next == nullptr)
					{
						f->next = p;
						p->next = nullptr;
						break;
					}
					else if (f->size < p->size && f->next->size > p->size)
					{
						p->next = f->next;
						f->next = p;
						break;
					}
					else
					{
						f = f->next;
					}
				}
			}
		}
		return reAddr;
	}
	
	//���Ӧ�㷨
	if (stra = 3)
	{
		if (sort == 1)
		{
			rd* f = freeq;
			if (p != freeq)
			{
				while (f->next != p)
				{
					f = f->next;
				}
				f->next = p->next;
			}
			else
			{
				freeq = freeq->next;
				if (freeq == nullptr)
				{
					freeq = p;
					return reAddr;
				}
			}
			f = freeq;
			while (f != nullptr)
			{
				if (f->size < p->size)
				{
					p->next = freeq;
					freeq = p;
					break;
				}
				else if (f->size > p->size&& f->next == nullptr)
				{
					f->next = p;
					p->next = nullptr;
					break;
				}
				else if (f->size > p->size && f->next->size < p->size)
				{
					p->next = f->next;
					f->next = p;
					break;
				}
				else
				{
					f = f->next;
				}
			}
		}
		return reAddr;
	}

	return -1;
}

//�ͷź���
void release(int a, int stra)
{
	rd* p = jobq;
	while (p != nullptr)
	{
		if (p->flag == a)
		{
			break;
		}
		else
		{
			p = p->next;
		}
	}

	rd* r = new rd(p->flag, p->size + 1); //������
	rd* f1 = freeq; //����
	rd* f2 = freeq; //����

	//Ѱ��f1
	while (f1 != nullptr)
	{
		if ((f1->flag + f1->size) == r->flag)
		{
			break;
		}
		else
		{
			f1 = f1->next;
		}
	}

	//Ѱ��f2
	while (f2 != nullptr)
	{
		if ((r->flag + r->size) == f2->flag)
		{
			break;
		}
		else
		{
			f2 = f2->next;
		}
	}

	//f1���У�f2�ѷ���
	if (f1 != nullptr && f2 == nullptr)
	{
		f1->size += r->size;
		r = f1;
	}
	
	//f1�ѷ��䣬f2����
	else if (f1 == nullptr && f2 != nullptr)
	{
		f2->flag = r->flag;
		f2->size += r->size;
		r = f2;
	}
	
	//f1���У�f2����
	else if (f1 != nullptr && f2 != nullptr)
	{
		f1->size += (r->size + f2->size);
		r = f1;
		rd* ff2 = freeq;
		if (f2 == freeq)
		{
			freeq = freeq->next;
		}
		else
		{
			while (ff2->next != f2)
			{
				ff2 = ff2->next;
			}
			ff2->next = f2->next;
		}
	}
	
	//�״���Ӧ�㷨
	if (stra == 1)
	{
		if (f1 == nullptr && f2 == nullptr)
		{
			if (freeq == nullptr)
			{
				freeq = r;
			}
			else
			{
				rd* f = freeq;
				while (f != nullptr)
				{
					if (f->flag < r->flag)
					{
						r->next = freeq;
						freeq = r;
						break;
					}
					else if (f->flag > r->flag && f->next == nullptr)
					{
						f->next = r;
						break;
					}
					else if (f->flag > r->flag && f->next->flag < r->flag)
					{
						r->next = f->next;
						f->next = r;
						break;
					}
					else
					{
						f = f->next;
					}
				}
			}
		}

		return;
	}

	//�����Ӧ�㷨
	if (stra == 2)
	{
		if (f1 != nullptr || f2 != nullptr)
		{
			if (r = freeq)
			{
				freeq = freeq->next;
			}
			else
			{
				rd* f = freeq;
				while (f->next != r)
				{
					f = f->next;
				}
				f->next = r->next;
			}
		}

		if (freeq == nullptr)
		{
			freeq = r;
		}
		else
		{
			rd* f = freeq;
			while (f != nullptr)
			{
				if (f->size > r->size)
				{
					r->next = freeq;
					freeq = r;
					break;
				}
				else if (f->size < r->size && f->next == nullptr)
				{
					f->next = r;
					r->next = nullptr;
					break;
				}
				else if (f->size < r->size && f->next->size > r->size)
				{
					r->next = f->next;
					f->next = r;
					break;
				}
				else
				{
					f = f->next;
				}
			}
		}

		return;
	}

	//���Ӧ�㷨
	if (stra = 3)
	{
		if (f1 != nullptr || f2 != nullptr)
		{
			if (r = freeq)
			{
				freeq = freeq->next;
			}
			else
			{
				rd* f = freeq;
				while (f->next != r)
				{
					f = f->next;
				}
				f->next = r->next;
			}
		}

		if (freeq == nullptr)
		{
			freeq = r;
		}
		else
		{
			rd* f = freeq;
			while (f != nullptr)
			{
				if (f->size < r->size)
				{
					r->next = freeq;
					freeq = r;
					break;
				}
				else if (f->size > r->size && f->next == nullptr)
				{
					f->next = r;
					r->next = nullptr;
					break;
				}
				else if (f->size > r->size && f->next->size < r->size)
				{
					r->next = f->next;
					f->next = r;
					break;
				}
				else
				{
					f = f->next;
				}
			}
		}

		return;
	}
}

int main()
{
	int strategy, operation;

	cout << "->PLEASE INPUT THE STRATEGY: 1->FIRST 2->BEST 3->WORST:" << endl;
	cin >> strategy;
	if (strategy != 1 && strategy != 2 && strategy != 3)
	{
		cout << "->STRATEGY DOES NOT EXIST. THE PROGRAM WILL EXIT." << endl;
		exit(1);
	}

	int loop = 1;
	while (loop == 1)
	{
		cout << "->PLEASE CHOOSE AN OPERATION: 1->REQUEST 2->RELEASE:" << endl;
		cin >> operation;
		
		//����
		if (operation == 1)
		{
			int isize, iflag;
			string iname;
			cout << "->PLEASE INPUT THE NAME AND SIZE NEEDED OF A JOB TO BE REQUESTED:" << endl;
			cin >> iname >> isize;
			iflag = request(isize, strategy);

			if (iflag == -1)
			{
				cout << "->MEMORY ALLOCATION FAILED. PLEASE INPUT AGAIN OR RELEASE A JOB FIRST." << endl;
				continue;
			}

			rd* j = new rd(iflag, isize, iname);
			if (jobq == nullptr)
			{
				jobq = j;
			}
			else
			{
				rd* last = jobq;
				while (last->next != nullptr)
				{
					last = last->next;
				}
				last->next = j;
			}
		}

		//�ͷ�
		else if (operation == 2)
		{
			if (jobq == nullptr)
			{
				cout << "->NO JOB IN MEMORY NOW. PLEASE REQUEST A JOB FIRST." << endl;
				continue;
			}

			string iname;
			cout << "->PLEASE INPUT THE NAME OF A JOB TO BE RELEASED:" << endl;
			cin >> iname;
			rd* p = jobq;
			while (p != nullptr)
			{
				if (p->name == iname)
				{
					release(p->flag, strategy);
					if (p == jobq)
					{
						jobq = jobq->next;
						break;
					}
					else
					{
						rd* f = jobq;
						while (f->next != p)
						{
							f = f->next;
						}
						f->next = p->next;
						break;
					}
				}
				else
				{
					p = p->next;
				}
			}

			if (p == nullptr)
			{
				cout << "->JOB TO BE RELEASED DOES NOT EXIST. PLEASE INPUT AGAIN CORRECTLY." << endl;
				continue;
			}
			delete p;
		}

		else
		{
			cout << "->OPERATION DOES NOT EXIST. PLEASE INPUT AGAIN CORRECTLY." << endl;
			continue;
		}

		//���ϵͳ��ǰ�ڴ�״̬
		rd* ftra = freeq;
		rd* jtra = jobq;
		cout << "**************************" << endl;
		cout << "->FREE MEMORY:" << endl;
		cout << "->(ADDRESS, SIZE)" << endl;
		if (ftra == nullptr)
		{
			cout << "->NO FREE MEMORY NOW." << endl;
		}
		while (ftra != nullptr)
		{
			cout << setw(10) << ftra->flag << setw(6) << (ftra->size - 1) << endl; //Ϊ����������Ԥ��һ����λ�ڴ�ռ�
			ftra = ftra->next;
		}
		cout << "->ALLOCATED MEMORY:" << endl;
		cout << "->(ADDRESS, SIZE, JOB)" << endl;
		if (jtra == nullptr)
		{
			cout << "->NO JOB IN MEMORY NOW." << endl;
		}
		while (jtra != nullptr)
		{
			cout << setw(10) << jtra->flag << setw(6) << jtra->size << setw(5) << jtra->name << endl;
			jtra = jtra->next;
		}
		cout << "**************************" << endl;

		cout << "->IS THERE ANY OPERATION ELSE? 1->YES 0->NO:" << endl;
		cin >> loop;
	}

	return 0;
}
