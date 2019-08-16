import {controlModel} from './index' 


const controller = {
    createUser(req,res){
      
    },

    getName(req,res){
      const temp = req.params.name //รับค่าจาก url เป็น params
      //const temp = req.name
      console.log(temp)
      controlModel.getName(temp).then((data) => {  //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).json({ "device_name": data }) 
      //res.status(200).json({ "device_name": "Suchada", "device_room": "Bedroom" })
      })
      
    }

}

export default controller 



/*'user strict';

var Customer = require('../appModel.js/index.js');

exports.list_all_customers = function(req,res){
    Customer.getAllCustomer(function(err,customer_fullName){
        console.log('Controller')
        if(err)
            res.send(err);
            console.log('res',customer_fullName);
        res.send(customer_fullName);
    });
};

exports.create_a_customer = function(req, res) {
  var new_customer = new Customer(req.body);

  //handles null error 
   if(!new_customer.customer_fullName || !new_customer.status){

            res.status(400).send({ error:true, message: 'Please provide customers/status' });

    }else{
        Customer.createCustomer(new_customer, function(err, customer_fullName) {
    
        if (err)
            res.send(err);
        res.json(customer_fullName);
    });
    }
};


exports.read_a_customer = function(req, res) {
    Customer.getCustomerById(req.params.customer_id, function(err, customer_fullName) {
    if (err)
      res.send(err);
    res.json(customer_fullName);
  });
};


exports.update_a_customer = function(req, res) {
    Customer.updateById(req.params.customer_id, new Customer(req.body), function(err, customer_fullName) {
    if (err)
      res.send(err);
    res.json(customer_fullName);
  });
};


exports.delete_a_customer = function(req, res) {

  Customer.remove( req.params.customer_id, function(err,customer_fullName) {
    if (err)
      res.send(err);
    res.json({ message: 'Customer successfully deleted' });
  });
};

*/

