
import controller from './controller'


export function setup(router){

    router.post('/api/json',controller.addTVRemote)
    //router.get('/:id',controller.getName)  //url = http://localhost:4000/controller/mashiro
    router.get('/tv/:button',controller.getTVRemote)
}
