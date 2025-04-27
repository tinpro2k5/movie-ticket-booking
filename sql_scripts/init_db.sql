CREATE TABLE IF NOT EXISTS User (
    userID INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    password VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    phone VARCHAR(20),
    isAdmin BOOLEAN DEFAULT FALSE
);

CREATE TABLE IF NOT EXISTS Movie (
    movieID INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    genre VARCHAR(50),
    description TEXT,
    duration INT,
    rating FLOAT,
    posterPath VARCHAR(255)
);

CREATE TABLE IF NOT EXISTS Theater (
    theaterID INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    location VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS Room (
    roomID INT AUTO_INCREMENT PRIMARY KEY,
    theaterID INT NOT NULL,
    name VARCHAR(50) NOT NULL,
    capacity INT NOT NULL,
    FOREIGN KEY (theaterID) REFERENCES Theater(theaterID)
);

CREATE TABLE IF NOT EXISTS Seat (
    roomID INT NOT NULL,
    seatNumber VARCHAR(10) NOT NULL,
    isVip BOOLEAN DEFAULT FALSE,
    PRIMARY KEY (roomID, seatNumber),
    FOREIGN KEY (roomID) REFERENCES Room(roomID)
);


CREATE TABLE IF NOT EXISTS Showtime (
    roomID INT NOT NULL,
    showDateTime DATETIME NOT NULL,
    movieID INT NOT NULL,
    PRIMARY KEY (roomID, showDateTime),
    FOREIGN KEY (roomID) REFERENCES Room(roomID),
    FOREIGN KEY (movieID) REFERENCES Movie(movieID)
);


CREATE TABLE IF NOT EXISTS Ticket (
    ticketID INT AUTO_INCREMENT PRIMARY KEY,
    userID INT NOT NULL,
    roomID INT NOT NULL,
    seatNumber VARCHAR(10) NOT NULL,
    showDateTime DATETIME NOT NULL,
    basePrice DECIMAL(10,2) NOT NULL,
    bookedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    isPaid BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (userID) REFERENCES User(userID),
    FOREIGN KEY (roomID, seatNumber) REFERENCES Seat(roomID, seatNumber),
    FOREIGN KEY (roomID, showDateTime) REFERENCES Showtime(roomID, showDateTime)
);


CREATE TABLE IF NOT EXISTS SeatSchedule (
    roomID INT NOT NULL,
    seatNumber VARCHAR(10) NOT NULL,
    showDateTime DATETIME NOT NULL,
    ticketID INT NULL,
    PRIMARY KEY (roomID, seatNumber, showDateTime),
    FOREIGN KEY (roomID, seatNumber) REFERENCES Seat(roomID, seatNumber),
    FOREIGN KEY (roomID, showDateTime) REFERENCES Showtime(roomID, showDateTime),
    FOREIGN KEY (ticketID) REFERENCES Ticket(ticketID)
);



INSERT IGNORE INTO User (username, password, email, phone, isAdmin) VALUES
('admin', 'adminpass', 'admin@example.com', '0123456789', TRUE),
('john_doe', 'password123', 'john@example.com', '0987654321', FALSE),
('jane_doe', 'password456', 'jane@example.com', '0111222333', FALSE);

-- Thêm Movie
INSERT IGNORE INTO Movie (title, genre, description, duration, rating, posterPath) VALUES
('Inception', 'Sci-Fi', 'A mind-bending thriller.', 148, 8.8, '/images/inception.jpg'),
('The Dark Knight', 'Action', 'The Batman faces Joker.', 152, 9.0, '/images/darkknight.jpg');

-- Thêm Theater
INSERT IGNORE INTO Theater (name, location) VALUES
('Cinema Center', '123 Main St'),
('Galaxy Theater', '456 Broadway Ave');

-- Thêm Room
INSERT IGNORE INTO Room (theaterID, name, capacity) VALUES
(1, 'Room A', 100),
(1, 'Room B', 80),
(2, 'Room C', 120);

-- Thêm Seat cho Room A
INSERT IGNORE INTO Seat (roomID, seatNumber, isVip) VALUES
(1, 'A1', FALSE),
(1, 'A2', FALSE),
(1, 'A3', TRUE),
(1, 'B1', FALSE),
(1, 'B2', TRUE);

-- Thêm Showtime
INSERT IGNORE INTO Showtime (roomID, showDateTime, movieID) VALUES
(1, '2025-05-01 18:00:00', 1),
(1, '2025-05-01 21:00:00', 2),
(2, '2025-05-01 19:00:00', 1);

-- Thêm Ticket mẫu
INSERT IGNORE INTO Ticket (userID, roomID, seatNumber, showDateTime, basePrice, isPaid) VALUES
(2, 1, 'A1', '2025-05-01 18:00:00', 100.00, TRUE),
(3, 1, 'B2', '2025-05-01 21:00:00', 120.00, FALSE);

-- Thêm SeatSchedule
INSERT IGNORE INTO SeatSchedule (roomID, seatNumber, showDateTime, ticketID) VALUES
(1, 'A1', '2025-05-01 18:00:00', 1),
(1, 'B2', '2025-05-01 21:00:00', 2),
(1, 'A2', '2025-05-01 18:00:00', NULL),
(1, 'A3', '2025-05-01 18:00:00', NULL),
(1, 'B1', '2025-05-01 18:00:00', NULL);
