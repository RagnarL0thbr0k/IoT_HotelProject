/**
 * Created by Utente on 17/07/2018.
 */

var dataFreeRoom = new Array();
var dataFreeGuest = new Array();
var dataNotFreeRoom = new Array();



function showFree() {

    try {

        $.get("http://40.114.200.254:3000/api/Room",function (data) {}).done(function (data) {

            for (var i = 0; i < data.length; i++){

                var id = data[i].roomId;
                var occupy = data[i].guestId;
                var permanence = data[i].permanence;


                if (occupy === "resource:org.hotel.network.HotelGuest#PH_Default" || occupy === "resource:org.hotel.network.HotelGuest#PH_ADMIN"){

                    dataFreeRoom.push('<h5 style="color: darkgreen">'+id+'   '+'</h5>');
                    Disp2(0);

                }else {
                    dataNotFreeRoom.push('<h5 style="color: darkred">'+id+'/'+occupy.substr(38)+'/'+(permanence)+'</h5>');
                    Disp2(2);

                }



            }

        }).fail(function() {
            alert( "Server is not online" );
        });

        //da migliorare, al momento si vedono tutti

        $.get("http://40.114.200.254:3000/api/HotelGuest", function (data2){}).done(function (data2) {
            for (var i = 0; i < data2.length; i++){

                var id = data2[i].guestId;
                var name = data2[i].firstName;
                var surname = data2[i].lastName;


                dataFreeGuest.push('<h5 style="color: darkgreen">'+id+'/'+name+'/'+surname+'   '+'</h5>');


                Disp2(1);

            }
        });


    }catch (error){
        alert("There is a server problem\n" + error);

    }

}

function roomBooking(){

    var roomID = prompt("Room ID: ");
    var guestID = prompt("Guest ID: ");
    var permanence = prompt("Permanence (arrive-leave): ");

    try {
        $.post("http://40.114.200.254:3000/api/RoomBooking",{

            "$class": "org.hotel.network.RoomBooking",
            "roomId": "resource:org.hotel.network.Room#"+ roomID,
            "guestId": "resource:org.hotel.network.HotelGuest#"+guestID,
            "permanence": permanence.toString()

        });

        alert("Booking success!");

        location.reload();

    }catch (error){
        alert("Room creation aborted.\n"+error);

    }
}

function dismissRoom() {

    try {

        var roomID = prompt("Room ID: ");

        $.post("http://40.114.200.254:3000/api/RoomFree",{

                "$class": "org.hotel.network.RoomFree",
                "roomId": "resource:org.hotel.network.Room#"+ roomID,
                "hostId": "resource:org.hotel.network.HotelGuest#PH_Default"

            });

        alert("Room dismiss with success!");

        location.reload();

    }catch (error){
        alert("There is a server problem\n" + error);

    }

}

function Disp2(identity) {
    var str='';
    var str2='';
    var str3='';


    if (identity === 0){
        for (var i=0;i<dataFreeRoom.length;i++)
        {
            str += dataFreeRoom[i] +'<hr>';  // adding each element with key number to variable
        }

        document.getElementById('free_rooms').innerHTML=str; // Display the elements of the array
    }
    if (identity === 1){
        for (var j=0;j<dataFreeGuest.length;j++)
        {
            str2 += dataFreeGuest[j] +'<hr>';  // adding each element with key number to variable
        }

        document.getElementById('free_guest').innerHTML=str2; // Display the elements of the array
    }

    if (identity === 2){
        for (var k=0;k<dataNotFreeRoom.length;k++)
        {
            str3 += dataNotFreeRoom[k] +'<hr>';  // adding each element with key number to variable
        }

        document.getElementById('reservation').innerHTML=str3; // Display the elements of the array
    }

}
