#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "renderers/raylib/clay_renderer_raylib.c"
#include "raylib.h"

const int FONT_ID_BODY_16 = 0;
Clay_Color COLOR_WHITE = {255, 255, 255, 255};

void RenderHeaderButton(Clay_String text) {
    CLAY(
        CLAY_LAYOUT({
            .padding = {16, 8}
        }),
        CLAY_RECTANGLE({
            .color = {140, 140, 140, 255},
            .cornerRadius = 5
        })
    ){
        CLAY_TEXT(text, CLAY_TEXT_CONFIG({
            .fontId = FONT_ID_BODY_16,
            .fontSize = 16,
            .textColor = {255, 255, 255, 255}
            })
        );
    };
};

void RenderHeaderItem(Clay_String text) {
    CLAY(
        CLAY_LAYOUT({
            .padding = {16, 8}
        })
    ){
        CLAY_TEXT(text, CLAY_TEXT_CONFIG({
            .fontId = FONT_ID_BODY_16,
            .fontSize = 16,
            .textColor = {255, 255, 255, 255}
            })
        );
    };
};

typedef struct {
    Clay_String title;
    Clay_String contents;
} Document;

typedef struct {
    Document *documents;
    uint32_t length;
} DocumentArray;

DocumentArray documents = {
    .documents = (Document[]){
        {.title = CLAY_STRING("Squirrels"), .contents = CLAY_STRING("Squirrels are fascinating creatures that inhabit various parts of the world. These small, furry animals are known for their agility, quick reflexes, and remarkable ability to adapt to different environments. One of the most intriguing aspects of squirrels is their unique lifestyle, which is characterized by a constant struggle for survival. Their lives are filled with terrors, as they must constantly be on the lookout for predators such as hawks and owls that can swoop down and snatch them from their treetop homes. Additionally, they must compete with other squirrels for food and resources, making their existence a daily struggle for survival. Despite these challenges, squirrels have developed remarkable strategies to cope with their environment. For instance, they have developed a keen sense of smell and hearing, which enables them to detect potential threats from a distance. They are also incredibly agile, able to leap from branch to branch with ease, making them difficult prey for predators. Furthermore, squirrels have developed a unique way of communicating with each other through a series of chirps, squeaks, and whistles, which helps them to coordinate their behavior and avoid danger. In conclusion, the lives of squirrels are a testament to their remarkable resilience and adaptability in the face of adversity. Their ability to thrive in a wide range of environments is a testament to their remarkable evolutionary success."),},
        {.title = CLAY_STRING("Monkeys"), .contents = CLAY_STRING("Monkeys are one of the most intelligent and fascinating creatures in the animal kingdom. With their advanced cognitive abilities, they have been observed using tools, solving problems, and even learning human sign language. Their intelligence is rivaled only by that of humans and dolphins, making them one of the most remarkable species on the planet. One of the most striking aspects of monkey behavior is their ability to use tools. In the wild, monkeys have been observed using sticks to extract termites from their mounds, rocks to crack open nuts, and even using leaves as umbrellas to protect themselves from the rain. This level of problem-solving ability is unmatched in the animal kingdom, and is a testament to their remarkable cognitive abilities. Furthermore, monkeys have been observed exhibiting complex social behavior, such as forming close bonds with each other, cooperating to achieve common goals, and even displaying cultural behaviors that are passed down from generation to generation. In captivity, monkeys have been taught to use sign language, allowing them to communicate with humans in a remarkable way. This has led to a greater understanding of their cognitive abilities, and has even raised questions about their capacity for self-awareness and consciousness. In conclusion, the intelligence and adaptability of monkeys make them one of the most fascinating species on the planet, and a testament to the remarkable diversity of life on Earth."),},
        {.title = CLAY_STRING("Elephants"), .contents = CLAY_STRING("Elephants are the largest land animals on the planet, and are known for their massive size, gentle nature, and remarkable intelligence. With their large ears, tusks, and wrinkled skin, they are one of the most recognizable and iconic species in the animal kingdom. One of the most significant impacts of elephants on their ecosystems is their role as 'keystone species.' This means that they play a crucial role in shaping their environment, and their presence has a significant impact on the other species that live in their ecosystem. For instance, their massive size allows them to create pathways and clearings that other animals can use, and their digging activities can create water sources that benefit other species. Furthermore, elephants have a remarkable ability to remember and mourn their dead, displaying a level of emotional intelligence that is unmatched in the animal kingdom. They have also been observed displaying empathy and compassion towards each other, and have even been known to adopt orphaned young from other species. In addition to their remarkable social behavior, elephants are also known for their remarkable physical abilities. Their large ears help them to regulate their body temperature, and their sensitive trunks allow them to feel and manipulate objects with great precision. In conclusion, elephants are a testament to the remarkable diversity and complexity of life on Earth, and their loss would have a significant impact on the ecosystems in which they live."),},
        {.title = CLAY_STRING("Penguins"), .contents = CLAY_STRING("Penguins are one of the most fascinating and unique species in the animal kingdom. Found in the Antarctic and sub-Antarctic regions, they have adapted to the harsh, cold climate in remarkable ways. One of the most striking aspects of penguins is their unique appearance, with their black and white feathers serving as camouflage in the sea and on the ice. Their wings have also evolved into flippers, allowing them to swim with great agility and speed through the water. This remarkable adaptation has enabled them to thrive in one of the most inhospitable environments on Earth. Penguins are also known for their remarkable social behavior, with many species forming large colonies that can number in the tens of thousands. Within these colonies, penguins have developed a complex system of communication, using a variety of calls and vocalizations to convey information and coordinate their behavior. Furthermore, penguins are remarkable parents, with many species taking turns incubating eggs and caring for their young. This level of parental investment is unmatched in the animal kingdom, and is a testament to the remarkable adaptability of penguins to their environment. In conclusion, penguins are a testament to the remarkable diversity and adaptability of life on Earth, and their unique appearance and behavior make them one of the most fascinating species on the planet."),},
    },
    .length = 4
};

uint32_t selectedDocumentIndex = 0;

void HandleSidebarInteraction(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        if (userData >= 0 && userData < documents.length) {
            selectedDocumentIndex = userData;
        }
    }
}

int main(void)
{
    int width = 900;
    int height = 700;
    const char* title = "Clay Application";
    Clay_Raylib_Initialize(width, height, title, FLAG_WINDOW_RESIZABLE);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena){
        .memory = malloc(clayRequiredMemory),
        .capacity = clayRequiredMemory,
    };
    Clay_Initialize(clayMemory, (Clay_Dimensions) {
        .width = width,
            .height = height
    });
    Clay_SetMeasureTextFunction(Raylib_MeasureText);
    Raylib_fonts[FONT_ID_BODY_16] = (Raylib_Font){
        .font = LoadFontEx("C:/Windows/Fonts/segoeui.ttf", 48, 0, 400),
        .fontId = FONT_ID_BODY_16
    };

    while (!WindowShouldClose())
    {
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            .width = GetScreenWidth(),
            .height = GetScreenHeight()
        });

        Vector2 mousePosition = GetMousePosition();
        Vector2 scrollDelta = GetMouseWheelMoveV();
        Clay_SetPointerState(
            (Clay_Vector2) {mousePosition.x, mousePosition.y},
            IsMouseButtonDown(0)
        );
        Clay_UpdateScrollContainers(
            true,
            (Clay_Vector2) {scrollDelta.x, scrollDelta.y},
            GetFrameTime()
        );

        Clay_Sizing layoutExpand = {
            .width = CLAY_SIZING_GROW(),
            .height = CLAY_SIZING_GROW()
        };
        Clay_RectangleElementConfig contentBackgroundConfig = {
            .color = {90, 90, 90, 255},
            .cornerRadius = 8
        };

        Clay_BeginLayout();

        CLAY(
            CLAY_ID("OuterContainer"),
            CLAY_RECTANGLE({ .color = {43, 41, 52, 255} }),
            CLAY_LAYOUT({ 
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = {
                    .width = CLAY_SIZING_GROW(),
                    .height = CLAY_SIZING_GROW(),
                },
                .padding = {16, 16},
                .childGap = 16
            })
        ) {
            CLAY(
                CLAY_ID("HeaderBar"),
                CLAY_RECTANGLE(contentBackgroundConfig),
                CLAY_LAYOUT({
                    .sizing = {
                        .height = CLAY_SIZING_FIXED(60),
                        .width = CLAY_SIZING_GROW(),
                    },
                    .padding = (16),
                    .childGap = 16,
                    .childAlignment = {
                        .y = CLAY_ALIGN_Y_CENTER
                    }
                })
            ) {
                CLAY(
                    CLAY_ID("FileButton"),
                    CLAY_LAYOUT({
                        .padding = {16, 8}
                    }),
                    CLAY_RECTANGLE({
                        .color = {140, 140, 140, 255},
                        .cornerRadius = 5
                    })
                ){
                    CLAY_TEXT(CLAY_STRING("File"), CLAY_TEXT_CONFIG({
                        .fontId = FONT_ID_BODY_16,
                        .fontSize = 16,
                        .textColor = {255, 255, 255, 255}
                        })
                    );

                    bool fileMenuVisible = Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FileButton"))) || Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FileMenu")));

                    if (fileMenuVisible) {
                        CLAY(
                            CLAY_ID("FileMenu"),
                            CLAY_FLOATING({
                                .attachment = {
                                    .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM
                                }
                            }),
                            CLAY_RECTANGLE({
                                .color = {40, 40, 40, 255},
                                .cornerRadius = 8
                            }),
                            CLAY_LAYOUT({
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                                .sizing = {
                                    .width = CLAY_SIZING_FIXED(200)
                                }
                            })
                        ) {
                            RenderHeaderItem(CLAY_STRING("New"));
                            RenderHeaderItem(CLAY_STRING("Open"));
                            RenderHeaderItem(CLAY_STRING("Close"));
                        };
                    }

                };
                RenderHeaderButton(CLAY_STRING("Edit"));
                CLAY(CLAY_LAYOUT({.sizing = {.width = CLAY_SIZING_GROW()}})){}
                RenderHeaderButton(CLAY_STRING("Upload"));
                RenderHeaderButton(CLAY_STRING("Media"));
                RenderHeaderButton(CLAY_STRING("Support"));
            };
            CLAY(
                CLAY_ID("LowerContent"),
                CLAY_LAYOUT({
                    .sizing = layoutExpand,
                    .childGap = 16
                })
            ) {
                CLAY(
                    CLAY_ID("Sidebar"),
                    CLAY_RECTANGLE(contentBackgroundConfig),
                    CLAY_LAYOUT({
                        .layoutDirection = CLAY_TOP_TO_BOTTOM,
                        .padding = {16, 16},
                        .childGap = 16,
                        .sizing = {
                            .width = CLAY_SIZING_FIXED(250),
                            .height = CLAY_SIZING_GROW()
                        }
                    })
                ){
                    for (int i =0; i <documents.length; i++) {
                        Document document = documents.documents[i];
                        Clay_LayoutConfig sidebarButtonLayout = {
                            .sizing = {.width=CLAY_SIZING_GROW()},
                            .padding = {16, 16}
                        };
                        if (i == selectedDocumentIndex ){
                            CLAY(
                                CLAY_LAYOUT(sidebarButtonLayout),
                                CLAY_RECTANGLE({
                                    .color={120, 120, 120, 255},
                                    .cornerRadius = 8,
                                })
                            ){
                                CLAY_TEXT(document.title, CLAY_TEXT_CONFIG({
                                    .fontId = FONT_ID_BODY_16,
                                    .fontSize = 16,
                                    .textColor = {255, 255, 255, 255}
                                    })
                                );
                            };
                        } else {
                            CLAY(
                                CLAY_LAYOUT(sidebarButtonLayout),
                                Clay_OnHover(HandleSidebarInteraction, i),
                                Clay_Hovered() 
                                    ? CLAY_RECTANGLE({.color={120, 120, 120, 120}})
                                    : 0
                            ){
                                CLAY_TEXT(document.title, CLAY_TEXT_CONFIG({
                                    .fontId = FONT_ID_BODY_16,
                                    .fontSize = 16,
                                    .textColor = {255, 255, 255, 255}
                                    })
                                );
                            };
                        };
                    };
                };
                CLAY(
                    CLAY_ID("MainContent"),
                    CLAY_RECTANGLE(contentBackgroundConfig),
                    CLAY_SCROLL({.vertical = true}),
                    CLAY_LAYOUT({
                        .layoutDirection = CLAY_TOP_TO_BOTTOM,
                        .childGap = 16,
                        .padding = {16, 16},
                        .sizing = layoutExpand
                    })
                ){
                    Document selectedDocument = documents.documents[selectedDocumentIndex];
                    CLAY_TEXT(selectedDocument.title, CLAY_TEXT_CONFIG({
                        .fontId = FONT_ID_BODY_16,
                        .fontSize = 24,
                        .textColor = COLOR_WHITE
                        })
                    );
                    CLAY_TEXT(selectedDocument.contents, CLAY_TEXT_CONFIG({
                        .fontId = FONT_ID_BODY_16,
                        .fontSize = 24,
                        .textColor = COLOR_WHITE
                        })
                    );
                };
            };
        };

        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands);
        EndDrawing();
    }
}