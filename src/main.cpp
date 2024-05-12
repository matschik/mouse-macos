#include <node_api.h>
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>

napi_value SetMousePosition(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    double x, y;
    napi_get_value_double(env, args[0], &x);
    napi_get_value_double(env, args[1], &y);

    CGPoint newPoint;
    newPoint.x = x;
    newPoint.y = y;
    CGEventRef move = CGEventCreateMouseEvent(
        NULL, kCGEventMouseMoved, newPoint, kCGMouseButtonLeft);
    CGEventPost(kCGHIDEventTap, move);
    CFRelease(move);

    return nullptr; // Return undefined
}

napi_value GetMousePosition(napi_env env, napi_callback_info info)
{
    CGPoint mouseLoc = CGEventGetLocation(CGEventCreate(NULL));

    napi_value obj, x_value, y_value;
    napi_create_object(env, &obj);

    // Create the napi_value for x coordinate
    napi_status status_x = napi_create_double(env, mouseLoc.x, &x_value);
    if (status_x != napi_ok)
        return nullptr; // Handle error appropriately

    // Set the x property
    napi_status set_x_status = napi_set_named_property(env, obj, "x", x_value);
    if (set_x_status != napi_ok)
        return nullptr; // Handle error appropriately

    // Create the napi_value for y coordinate
    napi_status status_y = napi_create_double(env, mouseLoc.y, &y_value);
    if (status_y != napi_ok)
        return nullptr; // Handle error appropriately

    // Set the y property
    napi_status set_y_status = napi_set_named_property(env, obj, "y", y_value);
    if (set_y_status != napi_ok)
        return nullptr; // Handle error appropriately

    return obj;
    // return nullptr;
}

// Utility function to determine mouse button and event types
void GetButtonAndEventType(int32_t buttonIndex, CGMouseButton *mouseButton, CGEventType *mouseDownType, CGEventType *mouseUpType)
{
    switch(buttonIndex) {
        case 1: // Right button
            *mouseButton = kCGMouseButtonRight;
            *mouseDownType = kCGEventRightMouseDown;
            *mouseUpType = kCGEventRightMouseUp;
            break;
        case 2: // Middle button
            *mouseButton = kCGMouseButtonCenter;
            *mouseDownType = kCGEventOtherMouseDown;
            *mouseUpType = kCGEventOtherMouseUp;
            break;
        default: // Left button or any other value
            *mouseButton = kCGMouseButtonLeft;
            *mouseDownType = kCGEventLeftMouseDown;
            *mouseUpType = kCGEventLeftMouseUp;
            break;
    }
}

void GetInputButton(napi_env env, napi_callback_info info, int32_t *button)
{
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (argc > 0) {
        napi_get_value_int32(env, args[0], button);
    }
}

// Helper function to create and post mouse events
void PostMouseEvent(CGEventType eventType, CGMouseButton button)
{
    CGPoint currentPoint = CGEventGetLocation(CGEventCreate(NULL));
    CGEventRef event = CGEventCreateMouseEvent(
        NULL, eventType, currentPoint, button);
    CGEventPost(kCGHIDEventTap, event);
    CFRelease(event);
}

napi_value MousePress(napi_env env, napi_callback_info info)
{
    int32_t button = 0;
    GetInputButton(env, info, &button);

    CGMouseButton mouseButton;
    CGEventType mouseDownType, mouseUpType;
    GetButtonAndEventType(button, &mouseButton, &mouseDownType, &mouseUpType);

    PostMouseEvent(mouseDownType, mouseButton);
    return nullptr;
}

napi_value MouseRelease(napi_env env, napi_callback_info info)
{
    int32_t button = 0;
    GetInputButton(env, info, &button);

    CGMouseButton mouseButton;
    CGEventType mouseDownType, mouseUpType;
    GetButtonAndEventType(button, &mouseButton, &mouseDownType, &mouseUpType);

    PostMouseEvent(mouseUpType, mouseButton);
    return nullptr;
}

napi_value MouseClick(napi_env env, napi_callback_info info)
{
    int32_t button = 0;
    GetInputButton(env, info, &button);

    CGMouseButton mouseButton;
    CGEventType mouseDownType, mouseUpType;
    GetButtonAndEventType(button, &mouseButton, &mouseDownType, &mouseUpType);

    PostMouseEvent(mouseDownType, mouseButton);
    PostMouseEvent(mouseUpType, mouseButton);
    return nullptr;
}

NAPI_MODULE_INIT(/* napi_env env, napi_value exports */)
{
    napi_status status;
    napi_value fn2, fn3, fn4, fn5, fn6;

    status = napi_create_function(env, NULL, 0, GetMousePosition, NULL, &fn2);
    if (status != napi_ok)
        return nullptr;
    status = napi_set_named_property(env, exports, "getMousePosition", fn2);
    if (status != napi_ok)
        return nullptr;

    status = napi_create_function(env, NULL, 0, SetMousePosition, NULL, &fn3);
    if (status != napi_ok)
        return nullptr;
    status = napi_set_named_property(env, exports, "setMousePosition", fn3);
    if (status != napi_ok)
        return nullptr;

    // Register and export MouseClick function
    status = napi_create_function(env, nullptr, 0, MouseClick, nullptr, &fn4);
    if (status != napi_ok)
        return nullptr;
    napi_set_named_property(env, exports, "mouseClick", fn4);

    // Register and export MousePress function
    status = napi_create_function(env, NULL, 0, MousePress, NULL, &fn5);
    if (status != napi_ok)
        return nullptr;
    napi_set_named_property(env, exports, "mousePress", fn5);

    // Register and export MouseRelease function
    status = napi_create_function(env, NULL, 0, MouseRelease, NULL, &fn6);
    if (status != napi_ok)
        return nullptr;
    napi_set_named_property(env, exports, "mouseRelease", fn6);

    return exports;
}
