import controller from './controller'


export function setup(router){

    router.post('/api/json',controller.addTVRemote)
    //router.get('/:id',controller.getName)  //url = http://localhost:4000/controller/mashiro
    router.get('/tv/:button',controller.getTVRemote)
    router.get('/remote_tv/tv_On/',controller.getButtonTV)
    router.post('/remote_tv/tv_On_post',controller.addTvOnPost)
}
