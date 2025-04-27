
SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


CREATE TABLE `customer_tb` (
  `id` int(11) NOT NULL,
  `name` varchar(50) NOT NULL DEFAULT '0',
  `phone` varchar(50) NOT NULL DEFAULT '0',
  `movie` varchar(50) NOT NULL DEFAULT '0',
  `format` varchar(50) NOT NULL DEFAULT '0',
  `seat` int(11) NOT NULL DEFAULT '0',
  `price` float NOT NULL DEFAULT '0',
  `showdate` varchar(50) NOT NULL DEFAULT '0',
  `showtime` varchar(50) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;



INSERT INTO `customer_tb` (`id`, `name`, `phone`, `movie`, `format`, `seat`, `price`, `showdate`, `showtime`) VALUES
(2, 'Rumi', '0114784878', 'Titanic', '3d', 4, 600, '0000-00-00', '04:20:00'),
(3, 'Kader', '01154878', 'Titanic', '2d', 3, 1050, '2012-01-01', '4:20');


CREATE TABLE `movie_tb` (
  `m_id` int(11) NOT NULL,
  `m_name` varchar(50) NOT NULL DEFAULT '0',
  `m_genre` varchar(50) NOT NULL DEFAULT '0',
  `m_format` varchar(50) NOT NULL,
  `m_showdate` varchar(50) NOT NULL,
  `m_showtime` varchar(50) NOT NULL,
  `m_ticketprice` float NOT NULL,
  `m_seat` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;



INSERT INTO `movie_tb` (`m_id`, `m_name`, `m_genre`, `m_format`, `m_showdate`, `m_showtime`, `m_ticketprice`, `m_seat`) VALUES
(1, 'Titanic', 'Romantic', '3d', '0000-00-00', '04:20:00', 150, 41),
(3, 'Titanic', 'Romantic', '2d', '2012-01-01', '4:20', 350, 42),
(4, 'The Detail', 'Action', '2d', '2017-11-01', '6:30PM', 200, 45),
(5, 'Tin TIn', 'Adventure', '2d', '2009-12-01', '3:20 PM', 500, 45),
(7, 'Tower Heist', 'Funny', '2d', '2017-12-12', '5:30 PM', 400, 45);


ALTER TABLE `customer_tb`
  ADD PRIMARY KEY (`id`);

ALTER TABLE `movie_tb`
  ADD PRIMARY KEY (`m_id`);


ALTER TABLE `customer_tb`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

ALTER TABLE `movie_tb`
  MODIFY `m_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
