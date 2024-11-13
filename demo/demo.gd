extends Control

var cell_size: Vector2
var pixel_pos: Vector2i

@onready var canvas: SimulatorCanvas = $SimulatorCanvas


func _ready() -> void:
    cell_size = Vector2(canvas.buffer_size) / Vector2(canvas.grid_size)


func _physics_process(_delta) -> void:
    if Input.is_mouse_button_pressed(MouseButton.MOUSE_BUTTON_LEFT):
        var mouse_pos = canvas.get_local_mouse_position()
        pixel_pos = floor(mouse_pos / cell_size)
    else:
        pixel_pos = Vector2i(-1, -1)
    canvas.update(pixel_pos)
