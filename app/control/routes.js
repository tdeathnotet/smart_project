import controller from './controller'


export function setup(router){
    router.post('/remote/button_on_post',controller.ButtonOnPost) //เก็บค่าปุ่มจาก หน้าบ้าน...

    //________________________DECODE TV REMOTE___________________________
    router.post('/api/remote_tv',controller.addTVRemote)  //เก็บข้อมูลจาก ESP8266
    router.post('/remote/decode/tv_remote',controller.decodeTVRemote)  //หน้าบ้านส่งปุ่มอะไรมา
    router.get('/remote/decode/tv_button',controller.decodeTVbutton)  //ส่งให้ ESP8266

    //________________________DECODE AC REMOTE___________________________
    router.post('/api/remote_ac',controller.addACRemote) //เก็บข้อมูลจาก ESP8266
    router.post('/remote/decode/ac_remote',controller.decodeACRemote) //หน้าบ้านส่งปุ่มอะไรมา
    router.get('/remote/decode/ac_button',controller.decodeACbutton) //ส่งให้ ESP8266
    //________________________DECODE FAN REMOTE___________________________



    router.get('/remote_on/button',controller.getButton) //เเสดงปุ่มที่กดจากหน้าบ้าน  เพื่อให้ ESP8266 เช็ค

    //--------------------------------------------TV---------------------------------
    router.get('/tv/:button',controller.getTVRemote) //เรียกค่าจาก MySQL
    //-------------------------------------------AC----------------------------------
    router.get('/ac/:button',controller.getACRemote) //เรียกค่าจาก MySQL
    //-------------------------------------------FAN----------------------------------


    //_________________________SMART GARDEN_________________________________________
    router.post('/api/smart_garden',controller.apiSmartGarden)  //ส่งข้อมูล sensor ไปเก็บไว้ใน MySQL
    router.post('/smartgarden/on_off',controller.getSwitch)  //เช็คว่ามีการกดปุ่มเปิด solenoid valve จากหน้าบ้านมาหรือไม่
    router.get('/smartgarden',controller.showSmartGarden) //แสดงค่า sensor 
    router.get('/smartgarden/status',controller.statusGarden) 
}
