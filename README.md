2 лабораторная работа по Паралельному программированию.

Задание:	Модифицировать программу из л/р №1 для параллельной работы по технологии OpenMP.

Доработка предыдущей лабораторной работы, заключавшаяся в добавлении возможности распаралеливать процесс (перемножения матриц). Были созданы 4 новых файла - stats_1, stats_2, stats_4, stats_8, - с размерами матриц (квадратных), объёмами работ,
и временем выполнения. Создание нового файла происходило путём изменения количества использоваемых потоков и названия файла в ручную. 

Графики и доверительные интервалы.
Для одного процесса:
![image](https://github.com/PripyatskyPrometheus/paralel_proga_2/assets/113877569/d1f55597-ea43-4804-bcdf-da655e4f1a70)
![image](https://github.com/PripyatskyPrometheus/paralel_proga_2/assets/113877569/85a95555-e9b7-49c9-acaf-a62dfefa7c53)


Для двух процессов:
![image](https://github.com/PripyatskyPrometheus/paralel_proga_2/assets/113877569/dd307875-c3f0-49dc-92b4-5338e737c1d6)
![image](https://github.com/PripyatskyPrometheus/paralel_proga_2/assets/113877569/9b8ac55f-eb01-4627-a273-53b3b53adf7b)


Для четырёх процессов:
![image](https://github.com/PripyatskyPrometheus/paralel_proga_2/assets/113877569/0780dba8-a8a5-479a-b667-33c3ff584c8b)
![image](https://github.com/PripyatskyPrometheus/paralel_proga_2/assets/113877569/15c10188-f67b-4a21-a253-2126e2130b03)


Для восьми процессов:
![image](https://github.com/PripyatskyPrometheus/paralel_proga_2/assets/113877569/48dfadac-20f0-46af-a4d4-5d3c481ff47c)
![image](https://github.com/PripyatskyPrometheus/paralel_proga_2/assets/113877569/d50b799b-193c-4601-8cd2-df280d86b44c)


Выводы: как можно видеть по результатам графиков и доверительных интервалов, увеличение количества потоков не сильно влияет на время выполнения процесса для матриц минимального размера (от 100); зато можно налблюдать не вооружённым глазом 
изменения для матриц макисмального размера (до 1 000), однако на последних графиках можно заметить, что разница во времени (чем больше потоков - тем меньше времени тратитпрограмма на выполнение) и для них становится не очень значимой.
Поэтому в подобного рода экспериментах стоит использовать матрицы гораздо больше размера.