import {controlModel} from './index' 


const controller = {
    addTVRemote(req,res){  // add TV remote
      //console.log(req)
      //console.log(req.body)
      controlModel.addTV_remote(req.body)  //ส่งข้อมูลไปเก็บยัง mySQL
    },
    getTVRemote(req,res){
      const reqButton = req.params.button //รับค่าจาก url เป็น params
      //const reqID = req.name
      console.log(reqButton)
      controlModel.getTV_remote(reqButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).json(rawData) //res.status(200).json({ "device_name": "Suchada", "device_room": "Bedroom" })
      })     
    }
}
export default controller 

