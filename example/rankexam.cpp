#include "../include/autorank.h"

int rankmain()
{
    //д������ʾ��
    scoredealer::Insert(scoreblock{"n123", time(NULL) - 100, 100ul});
    scoredealer::Insert(scoreblock{"n123456", time(NULL) + 200, 100000000ul});
    scoredealer::Insert(scoreblock{"n123456789", time(NULL) + 300, 1000000ul});
    scoredealer::Insert(scoreblock{"�����ַ�", time(NULL) - 500, 10000ul});
    scoredealer::Insert(scoreblock{"123����abc{_?", time(NULL) + 50, 114514ul});

    scoredealer::PrintList(1);
    scoredealer::WriteFile("test.dat");

    // //�������ʾ��
    scoredealer::ReadFile("test.dat");
    scoredealer::PrintList(1);

    //ʹ��˵��
    /*
    0.����autorank.h��autorank.cpp����Ҫ�ĵط�!!!!
    1.include"autorank.h"
    2.ʹ��scoredealer::ReadFile��ȡ��Ӧ�ķ����ļ� �ļ��������⵫Ҫ�̶� �Ƽ���[С��Ŀ��].dat
    3.ʹ��scoredealer::Insert(scoreblock{�������,��ǰʱ��(time(NULL)),�÷�(unsigned long������)})
    4.ʹ��scoredealer::WriteFile����
    */

   //����
   /*
   �ؼ������ݽṹ��
   ʹ��scoreblock�������ݿ�
   ʹ��vector���������б�

    ģ���ӿ�����:
    //��������ļ�
    //path :    ����ļ���ַ
    //����ֵ:   �ļ��쳣ʱ����false
    static bool WriteFile(const char* path);
    //д������ļ�
    //path :    ����ļ���ַ
    //����ֵ:   �ļ��쳣ʱ����false
    static bool ReadFile(const char* path);

    //�����������
    //layer:    ���ʱ����Ԥ������Ʊ����
    static void PrintList(int layer);
    //���������
    static void Insert(const scoreblock& obj);

    �㷨�ͳ�������:
    ��Ϊһ�������
    ��

    ϵͳʵ��:
    ���������ַ�������ʽ��ȡʵ�ֶ����������ʽ�Ķ�ȡ

    ���������
    ʵ����Ϸ������Ҫ�����а�
    �Զ�������ʽ�洢���ٿռ�ռ��
    ���Ӷ�ȡ�ٶ���Ч��
    ��ֹ��Ҵ۸���������
   */

    return 0;
}
