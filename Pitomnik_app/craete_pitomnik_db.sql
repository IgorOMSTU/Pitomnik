CREATE TABLE IF NOT EXISTS `Positions` (`ID_position` INTEGER PRIMARY KEY,`Position` VARCHAR(64) NOT NULL);
CREATE TABLE IF NOT EXISTS `Employees` (`ID_employee` INTEGER PRIMARY KEY, `FullName` VARCHAR(256) NOT NULL, `Address` VARCHAR(256) NOT NULL, `Salary` INT NOT NULL, `PhoneNumber` VARCHAR(64) NULL, `ID_position` INT NOT NULL, FOREIGN KEY (`ID_position`) REFERENCES `Positions` (`ID_position`) ON DELETE CASCADE ON UPDATE CASCADE);
CREATE TABLE IF NOT EXISTS `Clients` (`ID_client` INTEGER PRIMARY KEY, `FullName` VARCHAR(256) NOT NULL, `Address` VARCHAR(256) NULL, `PhoneNumber` VARCHAR(64) NULL, `e-mail` VARCHAR(64) NULL);
CREATE TABLE IF NOT EXISTS `Animals` (`ID_animal` INTEGER PRIMARY KEY, `Nickname` VARCHAR(64) NULL,`Gender` VARCHAR(1) NOT NULL, `Breed` VARCHAR(128) NOT NULL, `ID_employee` INT NOT NULL, 'Price' INT NOT NULL, FOREIGN KEY (`ID_employee`) REFERENCES`Employees` (`ID_employee`) ON DELETE CASCADE ON UPDATE CASCADE);
CREATE TABLE IF NOT EXISTS `Orders` (`ID_order` INTEGER PRIMARY KEY, `Date` DATE NOT NULL, `ID_animal` INT NOT NULL, `ID_client` INT NOT NULL, FOREIGN KEY (`ID_animal`) REFERENCES `Animals` (`ID_animal`) ON DELETE CASCADE ON UPDATE CASCADE, FOREIGN KEY (`ID_client`) REFERENCES `Clients` (`ID_client`) ON DELETE CASCADE ON UPDATE CASCADE);

INSERT INTO Positions VALUES(1, "Директор");
INSERT INTO Positions VALUES(2, "Бухгалтер");
INSERT INTO Positions VALUES(3, "Тренер");
INSERT INTO Positions VALUES(4, "Ветеринар");

INSERT INTO Clients VALUES (1, "Иванов Иван Иванович", "ул. Ленина, дом 53, квартира 11", "12-54-56", "ivanov@contozo.ru");
INSERT INTO Clients VALUES (2, "Петров Петр Петрович", "ул. 21 Амурская,  дом 17, квартира 16",  "22-64-57", "petrov@contozo.ru");
INSERT INTO Clients VALUES (3, "Сидоров Сидор Сидорович", "ул. Тюленина, дом 12, квартира 6", "32-74-28", "sidorov@contozo.ru");
INSERT INTO Clients VALUES (4, "Сергеев Сергей Сергеевич", "ул. Кирова, дом 33А, квартира 17", "42-84-59", "sergeev@contozo.ru");
INSERT INTO Clients VALUES (5, "Карасева Дарья Ивановна", "ул. Багратиона, дом 64, квартира 3", "72-33-54", "karaseva@contozo.ru");

INSERT INTO Employees VALUES (1, "Беляев Вячеслав Михайлович", "ул. Ленина, дом 53, квартира 11", 80000, "12-84-56", 1);
INSERT INTO Employees VALUES (2, "Рожкова Варвара Артёмовна", "ул. 21 Амурская,  дом 17, квартира 16", 70000, "22-44-57", 2);
INSERT INTO Employees VALUES (3, "Ефремов Михаил Фёдорович", "ул. Тюленина, дом 12, квартира 6", 70000, "32-64-58", 3);
INSERT INTO Employees VALUES (4, "Комаров Константин Романович", "ул. Кирова, дом 33А, квартира 17", 70000, "42-14-59", 4);

INSERT INTO Animals VALUES (1, "Тузик", "М", "АКИТА-ИНУ", 4, 4000);
INSERT INTO Animals VALUES (2, "Васька", "М", "Персидская кошка", 4, 5000);
INSERT INTO Animals VALUES (3, "Мурка", "Ж", "Сиамская кошка", 4, 6000);
INSERT INTO Animals VALUES (4, "Бобик", "М", "Корги", 4, 4000);
INSERT INTO Animals VALUES (5, "Шарик", "М", "Немецкая овчарка", 4, 3000);
INSERT INTO Animals VALUES (6, "Мурзик", "М", "Бенгальская кошка", 4, 5500);
INSERT INTO Animals VALUES (7, "Машка", "М", "Сиамская кошка", 4, 4000);
INSERT INTO Animals VALUES (8, "Даша", "М", "Персидская кошка", 4, 7000);

INSERT INTO Orders VALUES (1, "2021-01-17", 3, 2);
INSERT INTO Orders VALUES (2, "2021-02-18", 5, 1);
INSERT INTO Orders VALUES (3, "2021-03-19", 7, 2);
