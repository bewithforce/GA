**Отчет без госта**

Определимся с ф-цией для получения случайного числа. Как варианты возьмем старую ф-цию из стандартной библиотеки С и ф-цию из стандарта С++11, т.е. rand() и ф-цию со скрина ниже, соответственно.
![image-20210105182924880](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210105182924880.png) 

Для проверки их скорости выполним следующий кусок кода:

![image-20210105182242047](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210105182242047.png)

При использовании *default_random_engine* результат будет следующим:

![image-20210105182058408](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210105182058408.png)

Если же использовать *mt19937*, то результат будем иным:

![image-20210105182753082](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210105182753082.png)

Из описания стандарта и из результатов моего теста я могу сделать вывод, что с т.з скорости работы *default_random_engine*  является предпочтительным. Если важнее качество получаемых чисел, то выбор будет за *mt19937*. 

В своей работе я буду использовать более качественный.

Для каждой операции ГА я реализую несколько вариантов:

![image-20210106004240183](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210106004240183.png)

![image-20210106004228723](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210106004228723.png)

![image-20210106004252918](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210106004252918.png)

![image-20210106004303006](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210106004303006.png)

Запустив каждый из них я найду самую успешную комбинацию операторов для выбранной мною функции:

![image-20210106004425590](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210106004425590.png)

Запускать ГА я буду следующим образом:

![image-20210106004401351](C:\Users\Dzianis\AppData\Roaming\Typora\typora-user-images\image-20210106004401351.png)

Наилучший результат был достигнут при вероятности мутации в 8% с помощью randomReplication, bitwiseCross, bitwiseMutate и tournamentReduction.







