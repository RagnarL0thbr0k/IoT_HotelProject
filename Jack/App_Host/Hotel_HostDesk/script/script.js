/**
 * Created by Utente on 05/07/2018.
 */

var data = new Array();
//var data1 = new Array();

var dataGET = new Array();


// Gestisco la creazione di nuove camere e tabelle informative associate
function AddNewRoom() {

    var roomID = prompt("Room ID: ");
    var description = prompt("Description: ");
    var price = prompt("Price: ");

    if(confirm("Confirm your data?\nRoom ID: " + roomID + "\nDescription: " + description + "\nPrice: " + price)){

       try {
           $.post("http://40.114.200.254:3000/api/Room",
               {
                   "$class": "org.hotel.network.Room",
                   "roomId": roomID.toString(),
                   "description": description.toString(),
                   "price": price,
                   "access_code": " ",
                   "guestId": "resource:org.hotel.network.HotelGuest#PH_ADMIN",
                   "permanence": " "
               });

           data.push('<div class="card text-white bg-success col-lg-4 col-md-6 mb-4" id="free_room_table"><div class="card h-100">' +
               '<a href="#"><img class="card-img-top" src="img/hotel-room.jpg" alt=""></a>' +
               '<div class="card-body"><h4 class="card-title"><a href="#">'+ roomID +'</a></h4>' +
               '<h5 style="color: darkblue">'+ price.toString() + '$</h5><p class="card-text" style="color: black">'+ description.toString() +'</p></div><div class="card-footer">' +
               '<p style="color: green">AVAILABLE</p></div></div></div>');

           alert("Room successful created!");

           Disp();
       }catch(error) {
           alert("There was an error: \n" + error);
       }

    }else {
        alert("Room creation aborted.")
    }
}

function Disp() {
    var str='';

    //str = 'Total number of rooms : ' + data.length + '<br>';
    for (var i=0;i<data.length;i++)
    {
        str += data[i] + "<br >";  // adding each element with key number to variable
    }

    document.getElementById('rooms').innerHTML=str; // Display the elements of the array
}

//  Lista stanze esistenze
function showRooms() {

    try{
        $.get("http://40.114.200.254:3000/api/Room",function (data1) {
            dataGET.push(data1);


        }).done(function (data1) {

            for(var i = 0; i < data1.length; i++){

                var id = data1[i].roomId;
                var money = data1[i].price;
                var descr = data1[i].description;


                data.push('<div class="card text-white bg-success col-lg-4 col-md-6 mb-4" id="free_room_table"><div class="card h-100">' +
                    '<a href="#"><img class="card-img-top" src="img/hotel-room.jpg" alt=""></a>' +
                    '<div class="card-body"><h4 class="card-title"><a href="#">'+ id +'</a></h4>' +
                    '<h5 style="color: darkblue">'+ money + '$</h5><p class="card-text" style="color: black">'+ descr +'</p></div><div class="card-footer">' +
                    '<p style="color: green">AVAILABLE</p></div></div></div>');
            }

            Disp();

        }).fail(function() {
            alert( "Server in not online" );
        },"JSON");

        console.log(dataGET);
        console.log(data);

    }catch (error){
        alert("There was an error: \n" + error);
    }

}




