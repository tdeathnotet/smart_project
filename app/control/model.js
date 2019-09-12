//'user strict';
var sql = require('../db');
import pool from '../db' 

const controlModel = {
    addTV_remote({column,value,column2,value2}){
        console.log({column,value,column2,value2})
        return new Promise((resolve , reject) => {
            pool.query('UPDATE `tv_remote` SET '+column+' = ? , '+column2+' = ?' ,[value,value2], 
            function(err,result,fields){
                if(err) throw err;
                console.log("UPDATE " + column +" "+  column2)
                return resolve(result)
            })
        })
    },
    addAC_remote({column,value,column2,value2}){
        console.log({column,value,column2,value2})
        return new Promise((resolve , reject) => {
            pool.query('UPDATE `air_remote` SET '+column+' = ? , '+column2+' = ?' ,[value,value2], 
            function(err,result,fields){
                if(err) throw err;
                console.log("UPDATE " + column +" "+  column2)
                return resolve(result)
            })
        })
    },
    addFan_remote({column,value,column2,value2}){
        console.log({column,value,column2,value2})
        return new Promise((resolve , reject) => {
            pool.query('UPDATE `fan_remote` SET '+column+' = ? , '+column2+' = ?' ,[value,value2], 
            function(err,result,fields){
                if(err) throw err;
                console.log("UPDATE " + column +" "+  column2)
                return resolve(result)
            })
        })
    },
    getTV_remote(column,column2){
        return new Promise((resolve,reject) => {
            pool.query('SELECT '+column+','+column2+'  FROM `tv_remote`',
            function (error, results, fields) {
                if (error) throw error;
                    // console.log(results)
                    return resolve(results)
            }
            )
        }) //callback function
    },
    getAC_remote(column,column2){
        return new Promise((resolve,reject) => {
            pool.query('SELECT '+column+','+column2+'  FROM `air_remote`',
            function (error, results, fields) {
                if (error) throw error;
                    // console.log(results)
                    return resolve(results)
            }
            )
        }) //callback function
    },
    getFan_remote(column,column2){
        return new Promise((resolve,reject) => {
            pool.query('SELECT '+column+','+column2+'  FROM `fan_remote`',
            function (error, results, fields) {
                if (error) throw error;
                    // console.log(results)
                    return resolve(results)
            }
            )
        }) //callback function
    }
}

export default controlModel


