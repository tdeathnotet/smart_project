-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Aug 15, 2019 at 10:43 AM
-- Server version: 8.0.17
-- PHP Version: 7.3.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `smart_home`
--

-- --------------------------------------------------------

--
-- Table structure for table `devices`
--

CREATE TABLE `devices` (
  `device_id` int(11) NOT NULL,
  `device_name` text NOT NULL,
  `device_room` text NOT NULL,
  `wifi_user` varchar(50) NOT NULL,
  `wifi_pass` varchar(50) NOT NULL,
  `device_enable` bit(1) NOT NULL DEFAULT b'0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `devices`
--

INSERT INTO `devices` (`device_id`, `device_name`, `device_room`, `wifi_user`, `wifi_pass`, `device_enable`) VALUES
(1, 'Sorachai', 'Living Room', '', '', b'0'),
(2, 'Ponglada', 'BedRoom', '', '', b'0');

-- --------------------------------------------------------

--
-- Table structure for table `remote_air`
--

CREATE TABLE `remote_air` (
  `device_id` int(11) NOT NULL,
  `air_enable` bit(1) NOT NULL DEFAULT b'0',
  `air_speedDown` text NOT NULL,
  `air_power` text NOT NULL,
  `air_tempUp` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_tempDown` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_speedUp` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_timer` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `devices`
--
ALTER TABLE `devices`
  ADD PRIMARY KEY (`device_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `devices`
--
ALTER TABLE `devices`
  MODIFY `device_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
