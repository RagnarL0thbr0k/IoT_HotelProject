/**
 * Created by Utente on 05/07/2018.
 */

var dataRoom = new Array();
var dataHost = new Array();
var dataGuest = new Array();
var dataGET = new Array();
var id0;
var id1;
var n;
var r0mGuest;
var id;


// Gestisco la creazione di nuove camere e tabelle informative associate
function AddNewRoom() {

    var roomID = prompt("Room ID: ");
    var description = prompt("Description: ");
    var price = prompt("Price: ");
    var error =  "";
    var status = 0;

    if (roomID === "" || description === "" || price === "" || price <= 0){
        status = 1;
        error = "The room's field can not be empty!"
    }

    if((confirm("Confirm your data?\nRoom ID: " + roomID + "\nDescription: " + description + "\nPrice: " + price)) && status === 0){

       try {
           $.post("http://40.114.200.254:3000/api/Room",
               {
                   "$class": "org.hotel.network.Room",
                   "roomId": roomID.toString(),
                   "description": description.toString(),
                   "price": price,
                   "access_code": " ",
                   "guestId": "resource:org.hotel.network.HotelGuest#PH_Default",
                   "permanence": " "
               });

           dataRoom.push('<div class="card text-white bg-success col-lg-4 col-md-6 mb-4" id="free_room_table"><div class="card h-100">' +
               '<a href="#"><img class="card-img-top" src="img/hotel-room.jpg" alt=""></a>' +
               '<div class="card-body"><h4 class="card-title"><a href="#">'+ roomID +'</a></h4>' +
               '<h5 style="color: darkblue">'+ price.toString() + '$</h5><p class="card-text" style="color: black">'+ description.toString() +'</p></div><div class="card-footer">' +
               '<p style="color: green">AVAILABLE</p></div></div></div>');

           alert("Room successful created!");

           Disp(0);
       }catch(error) {
           alert("There was an error: \n" + error);
       }

    }else {
        alert("Room creation aborted.\n"+error);
    }
}

function Disp(identity) {
    var str='';

    //  Show room
    if (identity === 0){
        for (var i=0;i<dataRoom.length;i++)
        {
            str += dataRoom[i] + "<br>";  // adding each element with key number to variable
        }
    }
    document.getElementById('rooms').innerHTML=str; // Display the elements of the array
}

//  Lista stanze esistenze
function showRooms() {

    try{
        $.get("http://40.114.200.254:3000/api/Room",function (data1) {}).done(function (data1) {

            for(var i = 0; i < data1.length; i++){

                    var id1 = data1[i].roomId;
                    var money = data1[i].price;
                    var descr = data1[i].description;

                    dataRoom.push('<div class="card text-white bg-success col-lg-4 col-md-6 mb-4" id="free_room_table"><div class="card h-100">' +
                        '<a href="#"><img class="card-img-top" src="img/hotel-room.jpg" alt=""></a>' +
                        '<div class="card-body"><h4 class="card-title" id="'+id1+'" ><a  href="#">' + id1 + '</a></h4>' +
                        '<h5 style="color: darkblue">' + money + '$</h5><p class="card-text" style="color: black">' + descr + '</p></div><div class="card-footer">' +
                        '<p style="color: green">AVAILABLE</p></div></div></div>')

            }

            Disp(0);

        }).fail(function() {
            alert( "Server is not online" );
        },"JSON");

        //console.log(dataGET);
        //console.log(data);

    }catch (error){
        alert("There was an error: \n" + error);
    }

}

//  soo pulsanti con nome, alla pressione creo tabella completa

function AddNewHost() {

    var hostFirstName = prompt("First name: ");
    var hostLastName = prompt("Last name: ");
    var hostRole = prompt("Role: ");

    if(confirm("Confirm your data?\nFirst name: " + hostFirstName + "\nLast name: " + hostLastName + "\nRole: " + hostRole)){

        try {
            $.post("http://40.114.200.254:3000/api/HotelHost",
                {
                    "$class": "org.hotel.network.HotelHost",
                    "hostId": "PH_"+hostLastName,
                    "firstName": hostFirstName,
                    "lastName": hostLastName,
                    "role": hostRole
                });

            alert("Host successful created!");


        }catch(error) {
            alert("There was an error: \n" + error);
        }

    }else {
        alert("Host profile creation aborted.")
    }
}

function AddNewGuest() {

    var guestFirstName = prompt("First name: ");
    var guestLastName = prompt("Last name: ");
    var guestBday = prompt("Birth date: ");
    var guestTel = prompt("Telephone number: ");
    var guestEmail = prompt("Email: ");
    var guestNin = prompt("NIN: ");


    if(confirm("Confirm your data?\nFirst name: " + guestFirstName + "\nLast name: " + guestLastName + "\nBirthday: " + guestBday
        + "\nTelephone number: " + guestTel + "\nEmail: " + guestEmail + "\nNational Insurance Number: " + guestNin)){

        try {
            $.post("http://40.114.200.254:3000/api/HotelGuest",
                {
                    "$class": "org.hotel.network.HotelGuest",
                    "guestId": guestLastName+"_"+guestFirstName.charAt(0),
                    "firstName": guestFirstName,
                    "lastName": guestLastName,
                    "birthday": guestBday,
                    "telephone": guestTel,
                    "email": guestEmail,
                    "nin": guestNin
                });

            alert("Guest successful created!");


        }catch(error) {
            alert("There was an error: \n" + error);
        }

    }else {
        alert("Guest profile creation aborted.")
    }
}

//  page info stanza selezionata
function OpenInfo() {

    var x = document.getElementById("ID");
    var current_room_Id = x.value;

    if (current_room_Id === "" || current_room_Id.length !== 6){
        alert("ERROR\n  Insert a correct room ID")
    }else{
        try {
            $.get("http://40.114.200.254:3000/api/Room",function (data2){}).done(function (data2){
                for (var i = 0; i < data2.length; i++){

                    var r0mID = data2[i].roomId;
                    if ( r0mID === current_room_Id){
                        var  queryesString = "?"+current_room_Id;
                        window.open('/Hotel_HostDesk/room_info.html'+queryesString,'RoomInfo','width=1000,height=700');

                    }
                }
            }).fail(function(){ alert("error");
            });
        }catch (error){
            alert("There is a server problem\n" + error);
        }
    }
}

function Show() {

    var queryString = decodeURIComponent(window.location.search);
    queryString = queryString.substring(1);
    var queries = queryString.split("&");
    for (var i = 0; i < queries.length; i++)
    {
        id = queries[i];
    }

    try {
        $.get("http://40.114.200.254:3000/api/Room?filter=%7B%22roomId%22%3A%22"+id+"%22%7D",function (data3){}).done(function (data3){
            for (var i = 0; i < data3.length; i++){

                var r0mID = data3[i].roomId;
                var r0mAcOde = data3[i].access_code;
                r0mGuest = data3[i].guestId;
                var r0mPer = data3[i].permanence;

                if ( r0mID === id){
                    document.getElementById('room_name').innerHTML=r0mID;
                    document.getElementById('room_guest').innerHTML=r0mGuest.substr(38);
                    document.getElementById('room_code').innerHTML=r0mAcOde;
                    document.getElementById('room_permanence').innerHTML=r0mPer;
                }
            }

            getRoomData(id);
        }).fail(function(){ alert("Room info not found.");});



    }catch(error) {
        alert("There is a server problem\n" + error);

    }

}

function getRoomData(id) {
    $.get("https://apiazureprojectwork.azurewebsites.net/api/getTemp/"+id,function (dataStatus){}).done(function (dataStatus){
        for (var i = 0; i <= dataStatus.length; i++){

            var response = {"devname": dataStatus[i].devname.trim().toString(), "room_temp": dataStatus[i].room_temp, "status_door": dataStatus[i].status_door, "timestamp": dataStatus[i].timestamp, "flag": dataStatus[i].flag };
            var door = "Undefined";

                document.getElementById('room_temp').innerHTML = response.room_temp;

                if (dataStatus[i].status_door === 0){
                    door = "close";
                }else {
                    door = "!OPEN!";

                }
            document.getElementById('door_status').innerHTML = door;

        }

    }).fail(function(){ alert("Room info not found.");});
}

function setRoomTemp() {

    var temp = document.getElementById('newTemp').value;
    var guest = r0mGuest.substr(38);

    try {
        $.post("https://apiazureprojectwork.azurewebsites.net/api/setTemp/"+id+"/"+temp+"/"+guest+"",
            {
                "devname": id,
                "set_room_temp": temp,
                "timestamp": "1998-01-02T00:00:00.0000000",
                "user": guest,
                "flag": "1"
            });

        alert("New temperature insert with success!");

    }catch(error) {
        alert("There was an error: \n" + error);
    }
}
