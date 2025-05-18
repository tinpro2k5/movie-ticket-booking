SET time_zone = '+07:00';

CREATE TABLE IF NOT EXISTS User (
    userID INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    phone VARCHAR(20),
    isAdmin BOOLEAN DEFAULT FALSE
);

CREATE TABLE IF NOT EXISTS Movie (
    movieID INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(100) NOT NULL UNIQUE,
    genre VARCHAR(50),
    description TEXT,
    duration INT,
    rating FLOAT,
    posterPath VARCHAR(255),
    basePrice INT
);

CREATE TABLE IF NOT EXISTS Theater (
    theaterID INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL UNIQUE,
    location VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS Room (
    roomID INT NOT NULL,
    theaterID INT NOT NULL,
    name VARCHAR(50) NOT NULL,
    capacity INT NOT NULL,
    PRIMARY KEY (roomID, theaterID),
    FOREIGN KEY (theaterID) REFERENCES Theater(theaterID)
);

CREATE TABLE IF NOT EXISTS Seat (
    roomID INT NOT NULL,
    theaterID INT NOT NULL,
    seatNumber VARCHAR(10) NOT NULL,
    isVip BOOLEAN DEFAULT FALSE,
    PRIMARY KEY (roomID, theaterID, seatNumber),
    FOREIGN KEY (roomID, theaterID) REFERENCES Room(roomID, theaterID)
);


CREATE TABLE IF NOT EXISTS Showtime (
    roomID INT NOT NULL,
    theaterID INT NOT NULL,
    showDateTime DATETIME NOT NULL,
    movieID INT NOT NULL,
    PRIMARY KEY (roomID, theaterID, showDateTime),
    FOREIGN KEY (roomID, theaterID) REFERENCES Room(roomID, theaterID),
    FOREIGN KEY (movieID) REFERENCES Movie(movieID)
);


CREATE TABLE IF NOT EXISTS Ticket (
    ticketID INT AUTO_INCREMENT PRIMARY KEY,
    userID INT NOT NULL,
    roomID INT NOT NULL,
    theaterID INT NOT NULL, 
    seatNumber VARCHAR(10) NOT NULL,
    showDateTime DATETIME NOT NULL,
    basePrice DECIMAL(10,2) NOT NULL,
    bookedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    isPaid BOOLEAN DEFAULT FALSE,
    UNIQUE (roomID, theaterID, seatNumber, showDateTime),
    FOREIGN KEY (userID) REFERENCES User(userID),
    FOREIGN KEY (roomID, theaterID, showDateTime) 
    REFERENCES Showtime(roomID, theaterID, showDateTime)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);



CREATE TABLE IF NOT EXISTS SeatSchedule (
    roomID INT NOT NULL,
    theaterID INT NOT NULL,
    seatNumber VARCHAR(10) NOT NULL,
    showDateTime DATETIME NOT NULL,
    ticketID INT NULL,
    PRIMARY KEY (roomID, theaterID, seatNumber, showDateTime),
    FOREIGN KEY (roomID, theaterID, seatNumber) REFERENCES Seat(roomID, theaterID, seatNumber)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
    FOREIGN KEY (ticketID) REFERENCES Ticket(ticketID)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
    FOREIGN KEY (roomID, theaterID, showDateTime) REFERENCES Showtime(roomID, theaterID, showDateTime)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);



DELIMITER $$

DROP PROCEDURE IF EXISTS CreateRoomAndSeats$$

CREATE PROCEDURE CreateRoomAndSeats(
    IN roomID INT,
    IN theaterID INT,
    IN name VARCHAR(50),
    IN capacity INT
)
BEGIN
    DECLARE ROW_COUNT CHAR(1) DEFAULT 'A';
    DECLARE COL_COUNT INT DEFAULT 1;
    DECLARE IS_VIP BOOLEAN;

    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
    END;

    START TRANSACTION;

    INSERT IGNORE INTO Room (roomID, theaterID, name, capacity)
    VALUES (roomID, theaterID, name, capacity);

    WHILE ROW_COUNT <= 'C' DO
        WHILE COL_COUNT <= 5 DO
            SET IS_VIP = FALSE;
            IF ROW_COUNT = 'A' THEN
                SET IS_VIP = TRUE;
            END IF;

            INSERT IGNORE INTO Seat (
                roomID, theaterID, seatNumber, isVip
            ) VALUES (
                roomID, theaterID, CONCAT(ROW_COUNT, COL_COUNT), IS_VIP
            );

            SET COL_COUNT = COL_COUNT + 1;
        END WHILE;

        SET COL_COUNT = 1;
        SET ROW_COUNT = CHAR(ASCII(ROW_COUNT) + 1);
    END WHILE;

    COMMIT;
END$$

DELIMITER ;


DELIMITER $$

DROP PROCEDURE IF EXISTS DropShowtime$$

CREATE PROCEDURE DropShowtime(
    IN p_roomID INT,
    IN p_theaterID INT,
    IN p_showDateTime DATETIME
)
BEGIN
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
    END;

    START TRANSACTION;
    
    DELETE FROM SeatSchedule
    WHERE roomID = p_roomID AND theaterID = p_theaterID AND showDateTime = p_showDateTime;

    DELETE FROM Ticket
    WHERE roomID = p_roomID AND theaterID = p_theaterID AND showDateTime = p_showDateTime;

    DELETE FROM Showtime
    WHERE roomID = p_roomID AND theaterID = p_theaterID AND showDateTime = p_showDateTime;

    COMMIT;
END$$

DELIMITER ;

CREATE TABLE IF NOT EXISTS PricingRule (
    ruleID INT PRIMARY KEY AUTO_INCREMENT,
    ruleName VARCHAR(50) NOT NULL UNIQUE,
    description TEXT,
    isActive BOOLEAN DEFAULT TRUE
);


INSERT IGNORE INTO User (username, password, email, phone, isAdmin) VALUES
('john_doe', '10676640704186402002', 'john@example.com', '0987654321', FALSE),
('jane_doe', '10676640704186402002', 'jane@example.com', '0111222333', FALSE);


INSERT IGNORE INTO Movie (title, genre, description, duration, rating, posterPath, basePrice) VALUES
('Avatar', 'Sci-Fi', 'A journey to Pandora.', 162, 7.8, 'images/avatar.jpg', 100000),
('Titanic', 'Romance', 'A love story on the Titanic.', 195, 7.8, 'images/titanic.jpg', 120000),
('The Godfather', 'Crime', 'The story of a mafia family.', 175, 9.2, 'images/godfather.jpg' , 150000),
('Inception', 'Sci-Fi', 'A mind-bending thriller.', 148, 8.8, 'images/inception.jpg' , 130000),
('The Dark Knight', 'Action', 'The Batman faces Joker.', 152, 9.0, 'images/darkknight.jpg', 80000),
('Avengers: Endgame', 'Action', 'Superhero finale.', 180, 8.5, 'images/endgame.jpg', 90000),
('Inside Out', 'Animation', 'Emotion adventure.', 95, 8.2, 'images/insideout.jpg', 105000);



INSERT IGNORE INTO Theater (name, location) VALUES
('Cinema Center', '123 Main St'),
('Galaxy Theater', '456 Broadway Ave'),
('IMAX Theater', '789 Elm St'),
('Cineworld', '101 Oak St'),
('Regal Cinemas', '202 Pine St');




CALL CreateRoomAndSeats(1, 1, 'Room X', 100);
CALL CreateRoomAndSeats(2, 1, 'Room Y', 50);
CALL CreateRoomAndSeats(1, 2, 'Room A', 100);
CALL CreateRoomAndSeats(2, 2, 'Room B', 50);
CALL CreateRoomAndSeats(8, 2, 'Room C', 75);
CALL CreateRoomAndSeats(1, 3, 'Room D', 100);
CALL CreateRoomAndSeats(2, 3, 'Room E', 50);
CALL CreateRoomAndSeats(3, 3, 'Room F', 75);
CALL CreateRoomAndSeats(1, 4, 'Room G', 100);
CALL CreateRoomAndSeats(2, 4, 'Room H', 50);
CALL CreateRoomAndSeats(3, 4, 'Room I', 75);

INSERT IGNORE INTO Showtime (roomID, theaterID, showDateTime, movieID) VALUES
(8, 2, '2025-05-20 14:00:00', 1),
(8, 2, '2025-05-20 19:00:00', 1),
(8, 2, '2025-09-02 19:00:00', 2),
(8, 2, '2025-09-02 10:00:00', 2);

INSERT IGNORE INTO Ticket (userID, roomID, theaterID, seatNumber, showDateTime, basePrice, isPaid) VALUES
(1, 8, 2, 'B1', '2025-05-20 14:00:00', 100.00, TRUE),
(1, 8, 2, 'A1', '2025-05-20 19:00:00', 100.00, TRUE),
(2, 8, 2, 'A2', '2025-09-02 19:00:00', 100.00, TRUE),
(2, 8, 2, 'C3', '2025-09-02 10:00:00', 100.00, TRUE);




INSERT IGNORE INTO SeatSchedule (roomID, theaterID, seatNumber, showDateTime, ticketID) VALUES
(1, 1, 'A1', '2025-05-01 18:00:00', 1),
(1, 1, 'B2', '2025-05-01 21:00:00', 2),
(1, 1, 'C3', '2025-05-01 18:00:00', 3),
(1, 1, 'D4', '2025-05-01 21:00:00', 4),
(1, 1, 'E5', '2025-05-01 18:00:00', NULL),
(1, 1, 'F6', '2025-05-01 21:00:00', NULL),
(1, 1, 'A2', '2025-05-01 18:00:00', NULL),
(1, 1, 'A3', '2025-05-01 18:00:00', NULL),
(1, 1, 'B1', '2025-05-01 18:00:00', NULL),
(1, 1, 'B3', '2025-05-01 18:00:00', NULL),
(1, 1, 'C2', '2025-05-01 18:00:00', NULL),
(1, 1, 'C4', '2025-05-01 18:00:00', NULL),
(1, 1, 'D1', '2025-05-01 18:00:00', NULL),
(1, 1, 'D2', '2025-05-01 18:00:00', NULL),
(1, 1, 'E2', '2025-05-01 18:00:00', NULL),
(1, 1, 'E3', '2025-05-01 18:00:00', NULL),
(1, 1, 'F2', '2025-05-01 18:00:00', NULL),
(1, 1, 'F3', '2025-05-01 18:00:00', NULL),
(1, 1, 'A4', '2025-05-01 18:00:00', NULL),
(1, 1, 'B4', '2025-05-01 18:00:00', NULL),
(1, 1, 'C5', '2025-05-01 18:00:00', NULL),
(1, 1, 'D3', '2025-05-01 18:00:00', NULL),
(1, 1, 'E4', '2025-05-01 18:00:00', NULL),
(1, 1, 'F4', '2025-05-01 18:00:00', NULL);




INSERT IGNORE INTO PricingRule (ruleName, description) VALUES
('VIP_SEAT', 'Tăng giá cho ghế VIP'),
('EVENING_SHOWTIME', 'Tăng giá cho suất chiếu sau 18:00'),
('HOLIDAY', 'Tăng giá vào các ngày lễ'),
('STUDENT_DISCOUNT', 'Giảm giá cho học sinh/sinh viên');
