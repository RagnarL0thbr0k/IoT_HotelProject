/**
 * Created by Utente on 17/07/2018.
 */
var dataRoom = new Array();
var dataHost = new Array();
var nam3 = "";
var pswd = "";



function enter() {

    nam3 = document.getElementById('name').value;
    pswd = document.getElementById('pswd').value;

    try {

        $.get("http://40.114.200.254:3000/api/HotelHost ",function (data) {}).done(function (data) {

            for (var i = 0; i < data.length; i++){

                var id = data[i].hostId;

                if(id === nam3){
                    window.location.href = "index.html";
                }
            }

        }).fail(function() {
            alert( "Server is not online" );
        });


    }catch (error){
        alert("There is a server problem\n" + error);

    }

    //  pagina guest purtroppo mancante, implementabile

}

