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


INSERT IGNORE INTO User (username, password, email, phone, isAdmin) VALUES
('john_doe', 'password123', 'john@example.com', '0987654321', FALSE),
('jane_doe', 'password456', 'jane@example.com', '0111222333', FALSE);


INSERT IGNORE INTO Movie (title, genre, description, duration, rating, posterPath) VALUES
('Inception', 'Sci-Fi', 'A mind-bending thriller.', 148, 8.8, '/images/inception.jpg'),
('The Dark Knight', 'Action', 'The Batman faces Joker.', 152, 9.0, '/images/darkknight.jpg');


INSERT IGNORE INTO Theater (name, location) VALUES
('Cinema Center', '123 Main St'),
('Galaxy Theater', '456 Broadway Ave');


INSERT IGNORE INTO Room (roomID, theaterID, name, capacity) VALUES
(1, 1, 'Room A', 100),
(2, 1, 'Room B', 80),
(3, 2, 'Room C', 120);


INSERT IGNORE INTO Seat (roomID, theaterID, seatNumber, isVip) VALUES
(1, 1, 'A1', FALSE),
(1, 1, 'A2', FALSE),
(1, 1, 'A3', FALSE),
(1, 1, 'A4', FALSE),
(1, 1, 'A5', FALSE),
(1, 1, 'B1', FALSE),
(1, 1, 'B2', FALSE),
(1, 1, 'B3', FALSE),
(1, 1, 'B4', FALSE),
(1, 1, 'B5', FALSE),
(1, 1, 'C1', FALSE),
(1, 1, 'C2', FALSE),
(1, 1, 'C3', FALSE),
(1, 1, 'C4', FALSE),
(1, 1, 'C5', FALSE);



INSERT IGNORE INTO Showtime (roomID, theaterID, showDateTime, movieID) VALUES
(1, 1, '2025-05-01 18:00:00', 1),
(1, 1, '2025-05-01 21:00:00', 2);


INSERT IGNORE INTO Ticket (userID, roomID, theaterID, seatNumber, showDateTime, basePrice, isPaid) VALUES
(2, 1, 1, 'A1', '2025-05-01 18:00:00', 100.00, TRUE),
(3, 1, 1, 'B2', '2025-05-01 21:00:00', 120.00, FALSE);



INSERT IGNORE INTO SeatSchedule (roomID, theaterID, seatNumber, showDateTime, ticketID) VALUES
(1, 1, 'A1', '2025-05-01 18:00:00', 1),
(1, 1, 'B2', '2025-05-01 21:00:00', 2),
(1, 1, 'A2', '2025-05-01 18:00:00', NULL),
(1, 1, 'A3', '2025-05-01 18:00:00', NULL),
(1, 1, 'B1', '2025-05-01 18:00:00', NULL);

