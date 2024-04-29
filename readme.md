# memchecker 

memchecker - это программа для Windows, которая позволяет подробно узнать, как распределяется память на диске.


# Функциональность программы

- Анализирует файлы в указанной в качестве аргумента директории и выводит информацию о файлах и расходуемой памяти в графическом виде.

- Определяет принадлежность файлов к определенному классу программ.


# Алгоритм

1) Получить значение аргумента path
2) Выполнять listdir рекурсивно, пока не встретится файл 
3) Обработка файла:
  - ИИ определяет класс принадлежности
  - Определяется размер файла
  - Размер файла учитывается в общей памяти
  - Запоминается путь до файла
4) Выводится диаграмма
5) Пользователю предлагается удалить конкретный файл или отчистить целый класс


# Используемые подпрограммы/утилиты
  - Подпрограмма вывода информации в виде диаграммы
  - Параллельная обработка файлов в потоках OpenMP
  - Нейросеть на Python для определения класса принадлежности
  - Подпрограмма, запоминающая информацию о файлах
  - Подрограмма, обеспечивающая удаление и восстановление
  - Подрограмма для быстрого вызова программы


# Используемые тахнологии по шагам
1) C++
2) C++, OpenMP(?)
3) Python (ИИ), С++
4) PHP
5) C++
6) Bat или PowerShell (Быстрый вызов) 
7) Makefile (Сборка программы) 

* Шаги 6,7 не используется в основном алгоритме программы 


# Используемые ресурсы
  Навигация по дереву файлов https://eax.me/winapi-file-search/
  
  Веб-графика в R https://www.geeksforgeeks.org/interactive-charts-using-plotly-in-r/
  
  Макрос препроцессора errno https://www.geeksforgeeks.org/how-to-use-errno-in-cpp/
  
  <b>Win32API</b> Структура для описания файла https://learn.microsoft.com/ru-ru/windows/win32/api/fileapi/ns-fileapi-win32_file_attribute_data
  
  <b>Win32API</b> Функция извлечения метаданных https://learn.microsoft.com/ru-ru/windows/win32/api/fileapi/nf-fileapi-getfileattributesexa