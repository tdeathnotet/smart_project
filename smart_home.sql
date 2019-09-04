-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Sep 04, 2019 at 05:55 AM
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
-- Table structure for table `air_remote`
--

CREATE TABLE `air_remote` (
  `air_id` int(11) NOT NULL,
  `device_id` int(11) NOT NULL,
  `air_speedDown` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_power` text NOT NULL,
  `air_tempUp` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_tempDown` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_speedUp` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_timer` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `air_remote`
--

INSERT INTO `air_remote` (`air_id`, `device_id`, `air_speedDown`, `air_power`, `air_tempUp`, `air_tempDown`, `air_speedUp`, `air_timer`) VALUES
(0, 0, '', '554, 17962,  2990, 8954,  514, 478,  516, 1496,  492, 504,  492, 502,  490, 502,  466, 528,  464, 530,  464, 530,  490, 504,  492, 1524,  494, 476,  518, 476,  518, 1498,  492, 476,  520, 476,  516, 1496,  494, 1496,  494, 1524,  466, 1522,  440, 1550,  438, 530,  488, 506,  490, 506,  516, 478,  518, 476,  520, 476,  520, 474,  520, 476,  518, 476,  520, 476,  518, 478,  518, 478,  516, 480,  514, 502,  492, 502,  492, 502,  466, 528,  464, 530,  466, 528,  488, 508,  490, 504,  516, 478,  518, 476,  518, 476,  518, 476,  520, 476,  518, 476,  518, 476,  518, 476,  516, 480,  516, 480,  514, 502,  492, 1524,  440, 1550,  440, 1550,  462, 1526,  494, 2976,  2996, 8950,  520, 1496,  494, 476,  518, 476,  520, 476,  518, 478,  516, 478,  516, 480,  514, 502,  492, 502,  492, 1522,  442, 528,  464, 530,  464, 1552,  462, 506,  492, 502,  518, 1498,  492, 476,  518, 1498,  492, 1496,  494, 1496,  494, 1496,  494, 1522,  466, 1524,  442, 1548,  438, 1550,  464, 504,  516, 478,  518, 476,  520, 1496,  492, 1496,  494, 1496,  492, 478,  516, 480,  516, 480,  514, 502,  492, 502,  492, 1524,  440, 1550,  438, 530,  488, 1528,  490, 1500,  492, 1496,  494, 1496,  492, 1496,  494, 1496,  494, 478,  516, 480,  514, 502,  492, 502,  492, 502,  466, 528,  466, 530,  464, 1550,  464, 1526,  492, 1498,  492, 1496,  494', '', '', '', '');

-- --------------------------------------------------------

--
-- Table structure for table `devices`
--

CREATE TABLE `devices` (
  `device_id` int(10) NOT NULL,
  `device_name` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `device_room` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `wifi_user` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `wifi_pass` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `device_enable` bit(1) NOT NULL DEFAULT b'0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `devices`
--

INSERT INTO `devices` (`device_id`, `device_name`, `device_room`, `wifi_user`, `wifi_pass`, `device_enable`) VALUES
(1, 'Sorachai', 'Living Room', '', '', b'0'),
(2, 'Ponglada', 'BedRoom', '', '', b'0'),
(3, 'Suchada', 'Chicken', 'icute2', 'think2018', b'1');

-- --------------------------------------------------------

--
-- Table structure for table `tv_remote`
--

CREATE TABLE `tv_remote` (
  `tv_id` int(11) NOT NULL,
  `device_id` int(11) NOT NULL,
  `tv_On` text NOT NULL,
  `tv_volUp` text NOT NULL,
  `tv_volDown` text NOT NULL,
  `tv_OK` text NOT NULL,
  `tv_Up` text NOT NULL,
  `tv_Left` text NOT NULL,
  `tv_Right` text NOT NULL,
  `tv_Down` text NOT NULL,
  `tv_CHUp` text NOT NULL,
  `tv_CHDown` text NOT NULL,
  `tv_Return` text NOT NULL,
  `tv_Mute` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `air_remote`
--
ALTER TABLE `air_remote`
  ADD PRIMARY KEY (`air_id`);

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
  MODIFY `device_id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
