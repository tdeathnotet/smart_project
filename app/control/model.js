//'user strict';
var sql = require('../db');
import pool from '../db' 

const controlModel = {
    addTV_remote({column,value,column2,value2}){
        console.log({column,value,column2,value2})
        return new Promise((resolve , reject) => {
            //const tem = { air_power: 'Winnie', air_tempUp: 'Australia' };
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
            //const tem = { air_power: 'Winnie', air_tempUp: 'Australia' };
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
            //const tem = { air_power: 'Winnie', air_tempUp: 'Australia' };
            pool.query('UPDATE `air_remote` SET '+column+' = ? , '+column2+' = ?' ,[value,value2], 
            function(err,result,fields){
                if(err) throw err;
                console.log("UPDATE " + column +" "+  column2)
                return resolve(result)
            })
        })
    },
    getTV_remote(column){
        return new Promise((resolve,reject) => {
            pool.query('SELECT '+column+'  FROM `tv_remote`',
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


