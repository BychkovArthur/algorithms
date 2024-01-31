




print("? 0")
lvl, side = input(), input()
# 1 - 36
if (side == "main"):
    print("? 18")
    lvl, side = input(), input()
    # 1 - 18
    if (side == "main"):
        print("? 27")
        lvl, side = input(), input()
        # 1 - 9
        if (side == "main"):
            print("? 31")
            lvl, side = input(), input()
            # 1 - 5
            if (side == "main"):
                print("? 33")
                lvl, side = input(), input()
                # 1 - 3
                if (side == "main"):
                    print("? 34")
                    lvl, side = input(), input()
                    if (side == "main" and lvl == "low"):
                        print("! 1")
                    elif (side == "main" and lvl == "high"):
                        print("! 2")
                    if (side == "side" and lvl == "low"):
                        print("! 3")
                    if (side == "side" and lvl == "high"):
                        print("! 4")
                    # 4 - 5
                else:
                    print("? 32")
                    lvl, side = input(), input()
                    if (side == "main"):
                        print("! 4")
                    if (side == "side"):
                        print("! 5")
            # 6 - 9
            else:
                print("? 29")
                lvl, side = input(), input()
                # 6 - 7
                if side == "main":
                    print("? 30")
                    lvl, side = input(), input()
                    if (side == "main"):
                        print("! 6")
                    else:
                        print("! 7")
                # 8 - 9
                else:
                    print("? 28")
                    lvl, side = input(), input()
                    if side == "main":
                        print("! 8")
                    else:
                        print("! 9")
        # 10-18
        else:
            print("? 23")
            lvl, side = input(), input()
            # 10-13
            if (side == "main"):
                print("? 24")
                lvl, side = input(), input()
                if (side == "")