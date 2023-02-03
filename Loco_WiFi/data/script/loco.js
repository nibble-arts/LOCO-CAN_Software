// init functions
function init_loco() {

	load();
	update();
}


// update time and status
function update() {
	var today = new Date();
	var time = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();
	
	$(".time").text(time);

	get_status();
	setTimeout(update, 1000);
}


// disable content
function disable() {
	$(".online")
		.removeClass("enabled")
		.addClass("disabled")
		.attr("disabled", "disabled");

	$(".reload")
		.unbind("click");
}


// enable content
function enable() {
	$(".online")
		.removeClass("disabled")
		.addClass("enabled")
		.removeAttr("disabled");

	$(".reload").click(function() {
		load();
	})
}


// loading status
function update_action(text) {
	$(".action").text(text);
}


// get status from API
function get_status() {

	$.ajax({
		url: 'http://192.168.0.167/api?cmd=status',
		timeout: 4000,
		// dataType: "application/json",

		success: function (data) {
			enable();
			update_status(data.status);
		},

		error: function(xhr, status, error){
			disable();
			update_status({"type":"connecting..."});
			update_action("");
		}
	});
}


// update status
function update_status(status) {
	$(".status").text(status.type);
}


// load data from device
function load() {

	// $(".action").text("loading...");
	$(".reload").attr("src", "images/reload.gif");
	disable();
	update_action("loading...");


	// send request
	$.ajax({
		url: 'http://192.168.0.167/api?cmd=load',
		timeout: 4000,
		// dataType: "application/json",

		success: function (data) {

			clean_blocks();
			enable();

			$(".reload").attr("src", "images/reload.svg");
			update_action("loaded");

			// add received blocks
			$.each(data.data, function(k,v) {
				add_block(v)
			});

			update_status(data.status);
		},

		error: function(xhr, status, error){

			enable();
			$(".reload").attr("src", "images/reload.svg");
			update_action("loading failed");
		}
	});

	// setTimeout(load, 10000);
}


// append data block
// data = {type,uuid,data}
function add_block(data) {

	var struct = '<div class="block"><div class="type">' + data.type + '</div><div class="uuid">' + data.uuid + '</div><div class="data">' + data.data + '</div></div>';

	$(".content").append(struct);
}


function clean_blocks() {
	$(".content").empty();
}