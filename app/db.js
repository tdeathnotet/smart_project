import mysql from 'mysql';

const config = {
    host: "localhost",
    port: 3306,
    user: "root",
    password: "12345678",
    database : 'smart_home',
    connectionLimit: 100,
};

const pool = mysql.createPool(config);

export default pool;