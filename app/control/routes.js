
import controller from './controller'


export function setup(router){
    router.post('/api/temp',controller.showTemp)
    router.post('/api/jsonn',controller.showJson)
    router.get('/:id',controller.getName)  //url = http://localhost:4000/controller/mashiro
    // router.delete('/delete/:id')
}
//'use strict';
/* module.exports = function(app){


    
var todoList = require('../app/controller');

    applicationCache.route('/customers')
        .get(todoList.list_all_customers)
        .post(todoList.create_a_customer);


    app.route('/tasks/:taskId')
        .get(todoList.read_a_customer)
        .put(todoList.update_a_customer)
        .delete(todoList.delete_a_customer);
};*/

