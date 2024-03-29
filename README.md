# os_hw3

## Гареева Альбина БПИ218, Вариант 18
### [Задача о картинной галерее](https://edu.hse.ru/tokenpluginfile.php/65e7d670d96b789fead5df7141605abe/2398081/mod_resource/content/0/os_task_02.pdf)
#### [Критерии оценивания](https://edu.hse.ru/tokenpluginfile.php/65e7d670d96b789fead5df7141605abe/2415835/mod_resource/content/0/os_req_task03.pdf)
Вахтер–процесс следит за тем, чтобы в картинной галерее одновременно было не более 50 процессов–посетителей.  
Для обозрения представлены 5 картин. Посетитель случайным образом ходит от картины к картине, и если на картину любуются более чем десять посетителей, он стоит в стороне и ждет, пока число желающих увидеть картину не станет меньше.
Посетитель может покинуть галерею, когда просмотрит все картины. В галерею также пытаются постоянно зайти новые посетители, которые ожидают своей очереди, если та заполнена.  
Создать приложение, моделирующее однодневную работу картинной галереи.  
Время нахождения возле картины для каждого посетителя является случайной величиной в некотором диапазоне.  
Вахтер — сервер. Картинная галерея — клиент. Приходящиие посетители реализуются отдельным клиентом.  
При запуске программ требуемые для их работы IP адреса и порты задаются в командной строке, чтобы обеспечить гибкую подстройку к любой сети.

Все тестовые файлы находятся в папке [tests](https://github.com/argareeva/Gareeva-osi-idz3/tree/main/tests)   

## 4-5 баллов
Разработано клиент–серверное приложение, в котором сервер и клиенты независимо друг от друга отображают только ту информацию, которая поступает им во время обмена.  
То есть, отсутствует какой-либо общий вывод интегрированной информации, отображающий поведение системы в целом.  

Код сервера находится в [4-5_баллов_сервер.c](https://github.com/argareeva/Gareeva-osi-idz3/blob/main/4-5_%D0%B1%D0%B0%D0%BB%D0%BB%D0%BE%D0%B2_%D1%81%D0%B5%D1%80%D0%B2%D0%B5%D1%80.c)   
Код клиента находится в [4-5_баллов_клиенты.c](https://github.com/argareeva/Gareeva-osi-idz3/blob/main/4-5_%D0%B1%D0%B0%D0%BB%D0%BB%D0%BE%D0%B2_%D0%BA%D0%BB%D0%B8%D0%B5%D0%BD%D1%82%D1%8B.c)   
В примечаниях описана схема решаемой задачи  

## 6-7 баллов
В дополнение к программе на предыдущую оценку разработан дополнительный клиентский модуль, подключаемый к серверу, который предназначен для отображение комплексной информации о выполнении приложения в целом.  
То есть, данный программный модуль должен отображает поведение моделируемой системы, позволяя не пользоваться отдельными видами, предоставляемыми клиентами и серверами по отдельности.

Код находится в [6-7_баллов.c](https://github.com/argareeva/Gareeva-osi-idz3/blob/main/6-7_%D0%B1%D0%B0%D0%BB%D0%BB%D0%BE%D0%B2.c)  
В примечаниях описана схема решаемой задачи  

## 8 баллов
В дополнение к предыдущей программе реализована возможность подключения множества клиентов, обеспечивающих отображение информации о работе приложения.  
Это должно позволить осуществлять наблюдение за поведением программы с многих независимых компьютеров.   
При этом клиентов–наблюдателей можно отключать и подключать снова в динамическом режиме без нарушения работы всего приложения.  

Код находится в [8_баллов.c](https://github.com/argareeva/Gareeva-osi-idz3/blob/main/8_%D0%B1%D0%B0%D0%BB%D0%BB%D0%BE%D0%B2.c)  
В примечаниях описана схема решаемой задачи  

## 9 баллов
Разработано приложение, позволяющее отключать и подключать различных клиентов с сохранением работоспособности сервера.  
После этого можно вновь запускать отключенных клиентов, чтобы приложение в целом могло продолжить свою работу.

Код сервера находится в [9_баллов_сервер.c](https://github.com/argareeva/Gareeva-osi-idz3/blob/main/9_%D0%B1%D0%B0%D0%BB%D0%BB%D0%BE%D0%B2_%D1%81%D0%B5%D1%80%D0%B2%D0%B5%D1%80.c)   
Код клиента находится в [9_баллов_клиенты.c](https://github.com/argareeva/Gareeva-osi-idz3/blob/main/9_%D0%B1%D0%B0%D0%BB%D0%BB%D0%BE%D0%B2_%D0%BA%D0%BB%D0%B8%D0%B5%D0%BD%D1%82%D1%8B.c)   
В примечаниях описана схема решаемой задачи 
