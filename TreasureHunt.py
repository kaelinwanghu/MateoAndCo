print("? 2 2")
match int(input()):
    case 1:
        print("? 3 3")
        match int(input()):
            case 1:
                print("! 2 2")
            case 0:
                print("? 3 1")
                match int(input()):
                    case 1:
                        print("! 2 1")
                    case 0:
                        print("? 1 1")
                        match int(input()):
                            case 1:
                                print("! 1 1")
                            case 0:
                                print("! 1 2")
    case 0:
        print("? 4 2")
        match int(input()):
            case 1:
                print("? 3 1")
                match int(input()):
                    case 1:
                        print("! 3 1")
                    case 0:
                        print("? 4 1")
                        match int(input()):
                            case 1:
                                print("! 4 1")
                            case -0:
                                print("? 3 2")
                                match int(input()):
                                    case 1:
                                        print("! 3 2")
                                    case 0:
                                        print("! 4 2")
            case 0:
                print("? 2 4")
                match int(input()):
                    case 1:
                        print("? 2 3")
                        match int(input()):
                            case 1:
                                print("? 1 3")
                                match int(input()):
                                    case 1:
                                        print("! 1 3")
                                    case 0:
                                        print("! 2 3")
                            case 0:
                                print("? 1 4")
                                match int(input()):
                                    case 1:
                                        print("! 1 4")
                                    case 0:
                                        print("! 2 4")
                    case 0:
                        print("? 3 4")
                        match int(input()):
                            case 1:
                                print("? 3 3")
                                match int(input()):
                                    case 1:
                                        print("! 3 3")
                                    case 0:
                                        print("! 3 4")
                            case 0:
                                print("? 5 5")
                                match int(input()):
                                    case 1:
                                        print("! 4 4")
                                    case 0:
                                        print("! 4 3")