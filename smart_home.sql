-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Sep 10, 2019 at 03:10 PM
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
  `air_powerBuff` int(11) NOT NULL,
  `air_power` text NOT NULL,
  `air_tempUpBuff` int(11) NOT NULL,
  `air_tempUp` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_tempDownBuff` int(11) NOT NULL,
  `air_tempDown` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `air_speedFanBuff` int(11) NOT NULL,
  `air_speedFan` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

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
-- Table structure for table `fan_remote`
--

CREATE TABLE `fan_remote` (
  `fan_id` int(11) NOT NULL,
  `fan_OnBuff` int(11) NOT NULL,
  `fan_On` text NOT NULL,
  `fan_SpeedBuff` int(11) NOT NULL,
  `fan_Speed` text NOT NULL,
  `fan_SwingBuff` int(11) NOT NULL,
  `fan_Swing` text NOT NULL,
  `device_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `tv_remote`
--

CREATE TABLE `tv_remote` (
  `tv_id` int(11) NOT NULL,
  `device_id` int(11) NOT NULL,
  `tv_OnBuff` int(11) NOT NULL,
  `tv_On` text NOT NULL,
  `tv_VolUpBuff` int(11) NOT NULL,
  `tv_volUp` text NOT NULL,
  `tv_VolDownBuff` int(11) NOT NULL,
  `tv_volDown` text NOT NULL,
  `tv_OKBuff` int(11) NOT NULL,
  `tv_OK` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `tv_UpBuff` int(11) NOT NULL,
  `tv_Up` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `tv_LeftBuff` int(11) NOT NULL,
  `tv_Left` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `tv_RightBuff` int(11) NOT NULL,
  `tv_Right` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `tv_DownBuff` int(11) NOT NULL,
  `tv_Down` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `tv_CHUpBuff` int(11) NOT NULL,
  `tv_CHUp` text NOT NULL,
  `tv_CHDownBuff` int(11) NOT NULL,
  `tv_CHDown` text NOT NULL,
  `tv_ReturnBuff` int(11) NOT NULL,
  `tv_Return` text NOT NULL,
  `tv_MuteBuff` int(11) NOT NULL,
  `tv_Mute` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tv_remote`
--

INSERT INTO `tv_remote` (`tv_id`, `device_id`, `tv_OnBuff`, `tv_On`, `tv_VolUpBuff`, `tv_volUp`, `tv_VolDownBuff`, `tv_volDown`, `tv_OKBuff`, `tv_OK`, `tv_UpBuff`, `tv_Up`, `tv_LeftBuff`, `tv_Left`, `tv_RightBuff`, `tv_Right`, `tv_DownBuff`, `tv_Down`, `tv_CHUpBuff`, `tv_CHUp`, `tv_CHDownBuff`, `tv_CHDown`, `tv_ReturnBuff`, `tv_Return`, `tv_MuteBuff`, `tv_Mute`) VALUES
(1, 0, 99, '3502, 1710,  462, 378,  490, 1274,  462, 378,  488, 380,  488, 378,  490, 380,  488, 380,  488, 378,  488, 378,  490, 380,  488, 380,  488, 378,  490, 380,  486, 1276,  462, 380,  488, 380,  488, 378,  490, 378,  490, 382,  486, 382,  486, 380,  488, 380,  488, 380,  490, 1274,  462, 380,  488, 378,  490, 380,  488, 380,  488, 380,  490, 378,  490, 380,  488, 380,  512, 1250,  462, 380,  488, 1274,  462, 1274,  462, 1274,  462, 1276,  462, 380,  488, 378,  490, 1274,  462, 378,  490, 1274,  462, 1274,  462, 1274,  466, 1272,  486, 356,  488, 1276,  462', 99, '3458, 1752,  418, 424,  446, 1320,  416, 424,  444, 424,  444, 424,  444, 422,  444, 424,  446, 422,  444, 424,  446, 422,  444, 424,  444, 422,  444, 424,  444, 1320,  442, 398,  444, 424,  444, 422,  446, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  470, 1294,  418, 424,  444, 424,  444, 424,  466, 402,  446, 422,  470, 398,  444, 424,  444, 424,  444, 424,  444, 422,  446, 424,  444, 424,  444, 422,  444, 1322,  418, 422,  444, 424,  444, 424,  444, 422,  446, 424,  444, 422,  446, 422,  446, 1320,  418, 424,  444, 1320,  418', 99, '3456, 1754,  418, 424,  444, 1320,  418, 422,  444, 424,  446, 422,  444, 424,  444, 424,  444, 426,  444, 424,  444, 424,  446, 422,  444, 424,  442, 424,  446, 1318,  418, 424,  444, 424,  442, 426,  444, 424,  444, 424,  444, 424,  442, 424,  444, 424,  444, 424,  444, 1320,  418, 424,  444, 424,  444, 424,  444, 424,  444, 424,  446, 422,  446, 422,  444, 424,  444, 1320,  418, 422,  444, 424,  444, 424,  444, 424,  444, 1320,  418, 422,  444, 424,  444, 1320,  418, 424,  444, 424,  444, 424,  444, 424,  444, 1320,  418, 424,  444, 1320,  418', 99, '3500, 1710,  460, 380,  488, 1276,  460, 380,  490, 380,  486, 408,  460, 380,  488, 382,  484, 382,  488, 382,  486, 380,  488, 382,  486, 380,  488, 378,  490, 1276,  462, 378,  490, 380,  488, 380,  488, 382,  488, 382,  486, 380,  488, 380,  488, 380,  486, 384,  486, 1276,  462, 382,  486, 380,  488, 382,  486, 382,  486, 380,  488, 380,  488, 380,  486, 380,  488, 1276,  460, 380,  488, 380,  486, 1276,  460, 382,  486, 380,  486, 1276,  460, 382,  486, 1276,  462, 380,  486, 382,  486, 1264,  474, 382,  486, 382,  486, 1276,  462, 1276,  460', 99, '3502, 1686,  484, 380,  488, 1276,  460, 382,  486, 382,  486, 380,  488, 382,  488, 382,  484, 382,  486, 380,  488, 382,  486, 380,  488, 380,  486, 382,  486, 1276,  462, 382,  486, 384,  486, 380,  486, 382,  486, 382,  488, 380,  488, 382,  488, 382,  484, 382,  486, 1278,  458, 382,  488, 380,  486, 382,  486, 382,  486, 382,  486, 382,  488, 380,  486, 382,  488, 382,  486, 1278,  460, 382,  486, 1274,  460, 382,  486, 382,  486, 1276,  460, 380,  488, 380,  486, 1278,  460, 380,  488, 1276,  460, 382,  486, 380,  488, 1276,  462, 1252,  484', 99, '3458, 1728,  444, 422,  444, 1320,  418, 422,  444, 424,  444, 424,  444, 424,  446, 424,  444, 424,  444, 424,  444, 422,  446, 424,  444, 424,  446, 422,  444, 1320,  416, 424,  444, 424,  444, 422,  446, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 1320,  418, 422,  444, 424,  446, 422,  444, 424,  444, 422,  446, 424,  444, 424,  444, 424,  444, 424,  442, 1320,  418, 1320,  418, 1320,  418, 422,  446, 422,  444, 1320,  418, 424,  444, 424,  444, 1320,  442, 1294,  418, 1320,  418, 424,  442, 424,  444, 1320,  418, 1320,  418', 99, '3498, 1712,  428, 412,  506, 1260,  426, 414,  452, 418,  480, 386,  482, 386,  484, 384,  486, 382,  486, 382,  512, 356,  488, 380,  488, 380,  488, 376,  518, 1248,  460, 380,  488, 380,  514, 354,  488, 380,  488, 380,  514, 354,  490, 378,  514, 354,  490, 378,  490, 1254,  506, 354,  490, 380,  488, 378,  490, 378,  490, 380,  488, 378,  490, 376,  490, 376,  492, 1276,  462, 1274,  462, 1276,  462, 1276,  460, 380,  488, 380,  490, 1276,  486, 354,  488, 1274,  462, 1276,  486, 1252,  460, 1276,  460, 382,  488, 380,  512, 1252,  486, 1252,  460', 99, '3500, 1688,  484, 382,  486, 1276,  460, 382,  488, 382,  486, 382,  486, 382,  486, 380,  488, 380,  488, 380,  488, 380,  488, 380,  488, 382,  486, 380,  488, 1276,  460, 382,  486, 382,  486, 380,  488, 382,  486, 380,  488, 380,  488, 382,  486, 382,  488, 380,  486, 1254,  484, 378,  488, 382,  486, 382,  486, 380,  488, 382,  486, 382,  484, 382,  488, 378,  488, 1276,  460, 1276,  462, 380,  488, 1274,  462, 380,  488, 382,  486, 1276,  460, 380,  488, 1276,  460, 1276,  458, 382,  488, 1276,  460, 384,  486, 380,  486, 1276,  462, 1276,  460', 99, '3502, 1682,  488, 378,  490, 1274,  464, 376,  490, 378,  490, 378,  490, 380,  488, 378,  492, 378,  490, 380,  488, 378,  488, 380,  490, 378,  490, 378,  490, 1274,  462, 380,  490, 378,  490, 378,  490, 380,  490, 378,  490, 380,  488, 378,  490, 378,  490, 378,  490, 1274,  464, 378,  488, 382,  488, 378,  490, 380,  488, 380,  490, 376,  490, 378,  490, 380,  488, 380,  488, 380,  490, 1274,  462, 380,  488, 1252,  486, 1274,  462, 380,  488, 380,  488, 382,  486, 380,  488, 1274,  462, 378,  490, 1274,  462, 1274,  462, 378,  490, 1274,  462', 99, '3504, 1710,  462, 380,  488, 1276,  460, 380,  488, 382,  486, 380,  488, 378,  490, 380,  488, 380,  488, 380,  488, 380,  490, 380,  488, 378,  490, 378,  490, 1276,  460, 378,  490, 378,  490, 380,  488, 378,  490, 380,  488, 378,  490, 378,  490, 380,  490, 380,  488, 1276,  462, 378,  490, 380,  488, 380,  488, 378,  490, 378,  490, 378,  490, 380,  488, 376,  492, 1274,  462, 378,  514, 1250,  464, 378,  490, 1274,  464, 1274,  464, 378,  488, 378,  516, 1250,  486, 354,  490, 1274,  464, 376,  516, 1248,  464, 1274,  488, 352,  492, 1274,  464', 99, '3454, 1754,  444, 396,  468, 1298,  442, 396,  470, 398,  444, 422,  446, 422,  446, 422,  444, 424,  446, 424,  444, 424,  446, 422,  446, 422,  470, 398,  468, 1294,  444, 398,  470, 398,  446, 422,  446, 422,  444, 424,  470, 396,  446, 424,  446, 422,  470, 398,  474, 1292,  444, 396,  474, 394,  444, 424,  444, 424,  444, 422,  472, 396,  470, 398,  472, 396,  446, 422,  472, 396,  444, 1318,  420, 422,  444, 1318,  420, 422,  446, 1318,  420, 1318,  418, 422,  446, 422,  472, 1294,  418, 424,  470, 1294,  418, 422,  470, 1294,  418, 424,  470', 99, '3458, 1754,  418, 422,  444, 1320,  420, 422,  446, 422,  444, 424,  470, 396,  470, 398,  446, 424,  444, 424,  470, 398,  444, 422,  446, 422,  446, 422,  444, 1322,  444, 396,  446, 424,  444, 424,  444, 422,  446, 422,  446, 422,  444, 424,  472, 396,  444, 424,  470, 1294,  418, 424,  444, 424,  444, 424,  454, 412,  446, 422,  446, 424,  470, 396,  446, 422,  446, 422,  470, 1294,  444, 396,  446, 422,  444, 1320,  444, 1292,  418, 422,  446, 420,  470, 398,  444, 1320,  418, 422,  446, 422,  446, 1318,  418, 1318,  420, 422,  446, 1320,  418');

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
