#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

using namespace std;

struct PCB
{
	string name;
	int need; //����ʱ��
	int wait; //�ѵȴ�ʱ��
	int turn; //��תʱ��
	PCB* next;
};

int myclock = 0;
const int q = 7;
PCB* RQ1 = new PCB();
PCB* RQ2 = new PCB();
PCB* Finish = nullptr;

int main()
{
	string iname;
	int ineed, iwait;
	PCB* p = nullptr;
	PCB* t = nullptr;

	//���ļ�����
	ifstream read;
	read.open("rq.txt");

	PCB* q1 = RQ1;
	read >> iname >> ineed >> iwait;
	q1->name = iname;
	q1->need = ineed;
	q1->wait = iwait;
	for (int i = 2; i < 6; i++)
	{
		read >> iname >> ineed >> iwait;
		p = new PCB();
		p->name = iname;
		p->need = ineed;
		p->wait = iwait;
		q1->next = p;
		p = p->next;
		q1 = q1->next;
	}

	PCB* q2 = RQ2;
	read >> iname >> ineed >> iwait;
	q2->name = iname;
	q2->need = ineed;
	q2->wait = iwait;
	for (int i = 7; i < 11; i++)
	{
		read >> iname >> ineed >> iwait;
		p = new PCB();
		p->name = iname;
		p->need = ineed;
		p->wait = iwait;
		q2->next = p;
		p = p->next;
		q2 = q2->next;
	}

	read.close();

	//����RQ1
	while (RQ1 != nullptr)
	{
		p = RQ1;

		//����ʱ�����q
		if (RQ1->need > q)
		{
			myclock += q;
			RQ1->need -= q;
			RQ1 = RQ1->next;
			for (t = p; t->next != nullptr; t = t->next) {}
			p->next = nullptr;
			t->next = p;
		}

		//����ʱ�䲻����q
		else
		{
			myclock += RQ1->need;
			RQ1->turn = myclock + RQ1->wait;
			RQ1 = RQ1->next;
			p->next = nullptr;
			if (Finish == nullptr)
			{
				Finish = p;
			}
			else
			{
				for (t = Finish; t->next != nullptr; t = t->next) {}
				t->next = p;
			}
		}
	}

	//����RQ2
	while (RQ2 != nullptr)
	{
		p = RQ2;
		PCB* m = new PCB();
		PCB* f = RQ2;
		int min = RQ2->need;
		//Ѱ������ʱ����̵Ľ���
		for (t = p; t->next != nullptr; t = t->next)
		{
			if (t->next->need < min)
			{
				min = t->next->need;
				m = t->next;
				f = t;
			}
		}
		if (RQ2->next == nullptr)
		{
			m = RQ2;
			RQ2 = nullptr;
		}

		myclock += m->need;
		m->turn = myclock + m->wait;
		f->next = m->next;
		m->next = nullptr;
		if (Finish == nullptr)
		{
			Finish = m;
		}
		else
		{
			for (t = Finish; t->next != nullptr; t = t->next) {}
			t->next = m;
		}
	}

	//������̵���������תʱ��
	cout << setw(4) << "NAME" << setw(6) << "TURN" << endl;
	for (t = Finish; t != nullptr; t = t->next)
	{
		cout << setw(4) << t->name << setw(6) << t->turn << endl;
	}

	return 0;
}
