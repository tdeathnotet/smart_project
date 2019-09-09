import {controlModel} from './index' 

var TvOn = 0;

const controller = {
    addTVRemote(req,res){  // add TV remote
      //console.log(req)
      //console.log(req.body)
      contolModel.addTV_remote(req.body)  //ส่งข้อมูลไปเก็บยัง mySQL
    },
    getTVRemote(req,res){
      const reqButton = req.params.button //รับค่าจาก url เป็น params
      //const reqID = req.name
      console.log(reqButton)
      controlModel.getTV_remote(reqButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).send(rawData) //res.status(200).json({ "device_name": "Suchada", "device_room": "Bedroom" })
        //console.log(rawData)
      })
    },
      getButtonTV(req,res){
        res.json({"Tv_On": TvOn})

      },
      addTvOnPost(req, res){
        console.log(req.body.Tv_On)
        if(JSON.stringify(req.body.Tv_On)== 1){
          TvOn = "On"
        }else{
          TvOn = "Off"
        }
        res.status(400).json(req.body)
        // //TvOn = req.body.button;
      }
          
    
}
export default controller 
