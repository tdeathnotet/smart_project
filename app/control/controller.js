import {controlModel} from './index' 
//_____________ปุ่มรับ input การกดปุ่มต่างๆ _____________________-
var Button 
//____________ปุ่ม Decode TV________________________
var decode_TV 
var checkDecode_TV
//____________ปุ่ม Decode AC________________________
var decode_AC
var checkDecode_AC

//__________________data smartgarden______________
var smartGarden
var gardenOn_Off

const controller = {
    decodeTVRemote(req,res){
      var button_tv = req.body.button
      
      checkDecode_TV = req.body.status
      // console.log(req.body.status)
      // console.log(req.body.button)  //โชว์ปุ่มที่ต้องการ Decode

      if(button_tv == "decode_tvOn_Off" ){
        decode_TV = "tv_On"
      }if(button_tv == "decode_tvUp") {
        decode_TV = "tv_Up"
      }if(button_tv == "decode_tvDown") {
        decode_TV = "tv_Down"
      }if(button_tv == "decode_tvLeft") {
        decode_TV = "tv_Left"
      }if(button_tv == "decode_tvRight") {
        decode_TV = "tv_Right"
      }if(button_tv == "decode_tvOk") {
        decode_TV = "tv_OK"
      }if(button_tv == "decode_tvVol_up") {
        decode_TV = "tv_VolUp"
      }if(button_tv == "decode_tvVol_down") {
        decode_TV = "tv_VolDown"
      }if(button_tv == "decode_tvCh_up") {
        decode_TV = "tv_CHUp"
      }if(button_tv == "decode_tvCh_down") {
        decode_TV = "tv_CHDown"
      }if(button_tv == "decode_tvReturn") {
        decode_TV = "tv_Return"
      }if(button_tv == "decode_tvMute") {
        decode_TV = "tv_Mute"
      }

    }, 
    decodeTVbutton(req,res){
      res.status(200).json({ "Button" : decode_TV ,"Status" : checkDecode_TV })
    },
    decodeACRemote(req,res){
      var button_ac = req.body.button
      checkDecode_AC = req.body.status
      console.log(req.body.status)
      console.log(req.body.button)  //โชว์ปุ่มที่ต้องการ Decode
      
      if(button_ac == "decode_airPower"){
        decode_AC = "air_power"
      }if(button_ac == "decode_airTempUp"){
        decode_AC = "air_tempUp"
      }if(button_ac == "decode_airTempDown"){
        decode_AC = "air_tempDown"
      }if(button_ac == "decode_airFanSpeed"){
        decode_AC = "air_speedFan"
      }if(button_ac == "decode_airSwing"){
        decode_AC = "air_swing"
      }
    },
    decodeACbutton(req,res){
      res.status(200).json({ "Button" : decode_AC , "Status" : checkDecode_AC })
    },
    ButtonOnPost(req, res){
      var check = req.body.button
      console.log(req.body.button)

  //________________________TV Control____________________________________
      if(check == "tvOn_Off" ){
        Button = "tv_On"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvUp") {
        Button = "tv_Up"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvDown") {
        Button = "tv_Down"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvLeft") {
        Button = "tv_Left"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvRight") {
        Button = "tv_Right"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvOk") {
        Button = "tv_OK"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvVol_up") {
        Button = "tv_VolUp"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvVol_down") {
        Button = "tv_VolDown"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvCh_up") {
        Button = "tv_CHUp"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvCh_down") {
        Button = "tv_CHDown"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvReturn") {
        Button = "tv_Return"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "tvMute") {
        Button = "tv_Mute"
        setTimeout(function(){ Button = "0" }, 100)
  //______________________________FAN Control__________________________________________________
      }if(check == "fanOn_Off"){ 
        Button = "fan_On"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "fanSpeed"){
        Button = "fan_Speed"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "fanSwing"){
        Button = "fan_Swing"
        setTimeout(function(){ Button = "0" }, 100)
  //_______________________________Air Control_________________________________________________
      }if(check == "airPower"){
        Button = "air_power"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "airFanSpeed"){
        Button = "air_speedFan"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "airTempUp"){
        Button = "air_tempUp"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "airTempDown"){
        Button = "air_tempDown"
        setTimeout(function(){ Button = "0" }, 100)
      }if(check == "airSwing"){
        Button = "air_swing"
        setTimeout(function(){ Button = "0" }, 100)
      }
    },
    addTVRemote(req,res){  // add TV remote
      //console.log(req.body)
      controlModel.addTV_remote(req.body)
    },
    addACRemote(req,res){  // add AC remote
      //console.log(req.body)
      controlModel.addAC_remote(req.body)
    },
    addFanRemote(req,res){  // add AC remote
      //console.log(req.body)
      controlModel.addFan_remote(req.body)
    },
    getTVRemote(req,res){
      const reqTVButton = req.params.button //รับค่าจาก url เป็น params

      var buffTVButton = reqTVButton+"Buff"  //เพิ่มString Buff เพิ่แไปเช็คค่าในตาราง tv_OnBuff
      //console.log(reqButton , buffButton)
      controlModel.getTV_remote(reqTVButton,buffTVButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).send(rawData)
        //console.log(rawData)
      })
    },
    getACRemote(req,res){
      const reqACButton = req.params.button //รับค่าจาก url เป็น params

      var buffACButton = reqACButton+"Buff"  //เพิ่มString Buff เพิ่แไปเช็คค่าในตาราง tv_OnBuff
      //console.log(reqButton , buffButton)
      controlModel.getAC_remote(reqACButton,buffACButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).send(rawData) 
        //console.log(rawData)
      })
    },    
    getFanRemote(req,res){
      const reqFanButton = req.params.button //รับค่าจาก url เป็น params

      var buffFanButton = reqFanButton+"Buff"  //เพิ่มString Buff เพิ่แไปเช็คค่าในตาราง tv_OnBuff
      //console.log(reqButton , buffButton)
      controlModel.getFan_remote(reqFanButton,buffFanButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).send(rawData) 
        //console.log(rawData)
      })
    },
    getButton(req,res){  // ส่งต่าปุ่มจาก Font End ไปยัง ESP8266
      res.json({"Button" : Button })
    },
    apiSmartGarden(req,res){ //__________Smart garden__________
      console.log(req.body)  
      smartGarden = req.body
     controlModel.addSensor(req.body)  //ส่งค่าไปเก็บยัง mySQL

     //res.status(200).json(req.body)
    },

    showSmartGarden(req,res){
      res.json(smartGarden)
    },
    getSwitch(req,res){
      console.log(req.body.smart_garden)
      gardenOn_Off = req.body.smart_garden
    },
    statusGarden(req,res){
      res.json({"status" : gardenOn_Off })
    }

    
}
export default controller 
